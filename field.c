#include "field.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "error.h"
#include "logger.h"

#define MIN_ROWS 3
#define MIN_COLUMNS 3
#define MAX_ROWS 32
#define MAX_COLUMNS 32

struct field_t {
  int columns;
  int rows;
  piece_type_t** field;
  bool** free_region_checked;
  int free_cells;
};

static void check_dimensions(int rows, int columns) {
  if (rows < MIN_ROWS || rows > MAX_ROWS || columns < MIN_COLUMNS || columns > MAX_COLUMNS) {
    errorf("Wrong field dimensions.");
    tipf("Specify another row and column count between [%d; %d] and [%d; %d] correspondingly.", MIN_ROWS, MAX_ROWS, MIN_COLUMNS, MAX_COLUMNS);
    fatal(ERROR_WRONG_DIMENSIONS);
  }
}

field_t* create_field(int rows, int columns) {
  check_dimensions(rows, columns);

  field_t* field = malloc(sizeof(field_t));

  field->rows = rows;
  field->columns = columns;

  field->field = calloc(field->rows, sizeof(piece_type_t*));
  for (int row = 0; row < field->rows; row++) {
    field->field[row] = calloc(field->columns, sizeof(piece_type_t));
    for (int column = 0; column < field->columns; column++)
      field->field[row][column] = PIECE_TYPE_NONE;
  }

  field->free_region_checked = calloc(field->rows, sizeof(bool*));
  for (int row = 0; row < field->rows; row++)
    field->free_region_checked[row] = calloc(field->columns, sizeof(bool));

  field->free_cells = field->rows * field->columns;

  return field;
}
field_t* create_field_with_walls(int rows, int columns, bool** walls) { 
  field_t* field = create_field(rows, columns);

  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      if (walls[row][column]) {
        field->free_cells--;
        field->field[row][column] = PIECE_TYPE_WALL;
      }
    } 
  }


  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      if (field_get_free_region_size(field, row, column) % 5 != 0) {
        errorf("A region that cannot be filled with pentominoes exist.");
        tipf("Check the region at row %d column %d.", row + 1, column + 1);
        fatal(ERROR_WRONG_REGION);
      }
    }
  }

  if (field->free_cells > 60) {
    errorf("Too much free cells are on the field, it cannot be field with 12 pentominoes.");
    tipf("Reduce the amount of free cells by adding walls.");
    fatal(ERROR_TOO_MUCH_FREE_CELLS);
  }

  return field;
}

void destroy_field(field_t* field) {
  for (int row = 0; row < field->rows; row++) 
    free(field->field[row]);
  free(field->field);

  for (int row = 0; row < field->rows; row++) 
    free(field->free_region_checked[row]);
  free(field->free_region_checked);

  free(field);
}

bool field_cell_is_correct(field_t* field, int row, int column) {
  return row >= 0 && row < field->rows && column >= 0 && column < field->columns;
}
bool field_cell_is_free(field_t* field, int row, int column) {
  return field_cell_is_correct(field, row, column) && (field->field[row][column] == PIECE_TYPE_NONE);
}
bool field_is_completed(field_t* field) {
  return field->free_cells == 0;
}
void field_cell_find_free(field_t* field, int* row, int* column) {
  *row = 0;
  *column = 0;

  while (!field_cell_is_free(field, *row, *column)) {
    (*column)++;
    if (*column == field->columns) {
      *column = 0;
      (*row)++;
    }
  }
}
static int field_get_free_region_size_subroutine(field_t* field, int row, int column) {
  if (!field_cell_is_free(field, row, column))
    return 0;
  if (field->free_region_checked[row][column])
    return 0;

  field->free_region_checked[row][column] = true;

  int size = 1;
  size += field_get_free_region_size_subroutine(field, row - 1, column);
  size += field_get_free_region_size_subroutine(field, row + 1, column);
  size += field_get_free_region_size_subroutine(field, row, column + 1);
  size += field_get_free_region_size_subroutine(field, row, column - 1);

  return size;
  // int column1 = column;
  // int column2 = column;
  // int size = 0;

  // while (field_cell_is_free(field, row, column1 - 1)) column1--;
  // while (field_cell_is_free(field, row, column2 + 1)) column2++;

  // size = column2 - column1 + 1;

  // for (int column0 = column1; column0 <= column2; column0++) {

  // }
}
int field_get_free_region_size(field_t* field, int row, int column) {
  for (int row = 0; row < field->rows; row++)
    for (int column = 0; column < field->columns; column++)
      field->free_region_checked[row][column] = false;
  return field_get_free_region_size_subroutine(field, row, column);
}
bool field_wrong_region_exists(field_t* field) {
  for (int row = 0; row < field->rows; row++) {
    for (int column = 0; column < field->columns; column++) {
      int block_size = field_get_free_region_size(field, row, column);
      //printf("%d\n", block_size);
      if (block_size % 5 != 0)
        return true;
    }
  }
  //draw_field(field);
  //exit(-1);
  return false;
}

static void field_put_piece(field_t* field, piece_t* piece, int row, int column) {
  field->field[row][column] = piece->type;
  for (int piece_block_number = 0; piece_block_number < PIECE_BLOCK_COUNT - 1; piece_block_number++) {
    piece_block_t piece_block = piece->blocks[piece_block_number];
    int piece_block_row = row + piece_block.row_offset;
    int piece_block_column = column + piece_block.column_offset;

    field->field[piece_block_row][piece_block_column] = piece->type;
  }
  field->free_cells -= 5;
}
static bool field_can_piece_be_placed(field_t* field, piece_t* piece, int row, int column) {
  if (!field_cell_is_free(field, row, column))
    return false;

  for (int piece_block_number = 0; piece_block_number < PIECE_BLOCK_COUNT - 1; piece_block_number++) {
    piece_block_t piece_block = piece->blocks[piece_block_number];
    int piece_block_row = row + piece_block.row_offset;
    int piece_block_column = column + piece_block.column_offset;

    if (!field_cell_is_free(field, piece_block_row, piece_block_column)) {
      return false;
    }
  }
  return true;
}
bool field_try_to_put_piece(field_t* field, piece_t* piece, int row, int column) {
  if(!field_can_piece_be_placed(field, piece, row, column))
    return false;
  field_put_piece(field, piece, row, column);
  return true;
}

void field_remove_piece(field_t* field, piece_t* piece, int row, int column) {
  field->field[row][column] = PIECE_TYPE_NONE;
  for (int piece_block_number = 0; piece_block_number < PIECE_BLOCK_COUNT - 1; piece_block_number++) {
    piece_block_t piece_block = piece->blocks[piece_block_number];
    int piece_block_row = row + piece_block.row_offset;
    int piece_block_column = column + piece_block.column_offset;

    field->field[piece_block_row][piece_block_column] = PIECE_TYPE_NONE;
  }
  field->free_cells += 5;
}

char draw_buffer[96][500];
char* draw_block_buffers[16][3] = {
  {
    "▛▀▜",
    "▌ ▐",
    "▙▄▟"
  },
  {
    "▌ ▐",
    "▌ ▐",
    "▙▄▟"
  },
  {
    "▛▀▀",
    "▌  ",
    "▙▄▄"
  },
  {
    "▌ ▝",
    "▌  ",
    "▙▄▄"
  },
  {
    "▛▀▜",
    "▌ ▐",
    "▌ ▐"
  },
  {
    "▌ ▐",
    "▌ ▐",
    "▌ ▐"
  },
  {
    "▛▀▀",
    "▌  ",
    "▌ ▗"
  },
  {
    "▌ ▝",
    "▌  ",
    "▌ ▗"
  },
  {
    "▀▀▜",
    "  ▐",
    "▄▄▟"
  },
  {
    "▘ ▐",
    "  ▐",
    "▄▄▟"
  },
  {
    "▀▀▀",
    "   ",
    "▄▄▄"
  },
  {
    "▘ ▝",
    "   ",
    "▄▄▄"
  },
  {
    "▀▀▜",
    "  ▐",
    "▖ ▐"
  },
  {
    "▘ ▐",
    "  ▐",
    "▖ ▐"
  },
  {
    "▀▀▀",
    "   ",
    "▖ ▗"
  },
  {
    "▘ ▝",
    "   ",
    "▖ ▗" 
  }
};


typedef enum {
  DIRECTION_TOP = 0x1,
  DIRECTION_RIGHT = 0x2,
  DIRECTION_DOWN = 0x4,
  DIRECTION_LEFT = 0x8
} direction_t;

void draw_pretty_field(field_t* field) {
  bzero(draw_buffer, sizeof(draw_buffer));
  for (int row = 0; row < field->rows; row++) {
    for (int column = 0; column < field->columns; column++) {
      piece_type_t piece_type = field->field[row][column];

      if (piece_type == PIECE_TYPE_WALL) {
        for (int i = 0; i < 3; i++) {
          strcat(draw_buffer[row * 3 + i], BG_COLOR_NORMAL);
          strcat(draw_buffer[row * 3 + i], "   ");
        }
        continue;
      }

      int neighbours = 0;

      if (field_cell_is_correct(field, row - 1, column) && field->field[row - 1][column] == piece_type) neighbours |= DIRECTION_TOP;
      if (field_cell_is_correct(field, row, column + 1) && field->field[row][column + 1] == piece_type) neighbours |= DIRECTION_RIGHT;
      if (field_cell_is_correct(field, row + 1, column) && field->field[row + 1][column] == piece_type) neighbours |= DIRECTION_DOWN;
      if (field_cell_is_correct(field, row, column - 1) && field->field[row][column - 1] == piece_type) neighbours |= DIRECTION_LEFT;

      char** draw_block_buffer = draw_block_buffers[neighbours];

      for (int i = 0; i < 3; i++) {
        strcat(draw_buffer[row * 3 + i], piece_type_get_color(piece_type));
        strcat(draw_buffer[row * 3 + i], draw_block_buffer[i]);
      }
    }
  }

  printf("\n");

  for (int row = 0; draw_buffer[row][0] != '\0'; row++)
    printf("%s" BG_COLOR_NORMAL "\n", draw_buffer[row]);
  printf("\n");
}
void draw_field(field_t* field) {
  printf("\n");
  for (int row = 0; row < field->rows; row++) {
    for (int i = 0; i < 2; i++) {
      for (int column = 0; column < field->columns; column++) {
        piece_type_t piece_type = field->field[row][column];

        if (piece_type == PIECE_TYPE_NONE) {
          printf("  ");
        } else {
          printf("%s", piece_type_get_color(piece_type));
          printf("██");
          printf(FG_COLOR_NORMAL);
        }

        if (column != field->columns - 1)
          printf("║");
      }
      printf("\n");


    }
    if (row != field->rows - 1) {
      for(int i = 0; i < field->columns * 3 - 1; i++) {
        if ((i - 2) % 3 == 0)
          printf("╬");
        else
          printf("═");
      }
    }
    printf("\n");
  }
}
