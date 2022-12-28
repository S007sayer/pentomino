#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "error.h"
#include "game.h"
#include "logger.h"

#define FIELD_DEFINITION_FILE "fielddef.txt"

static void intro() {
  logf("Welcome to the Pentomino app!");
}

static FILE* open_field_definition_file() {
  logf("Reading the field definition file '" FIELD_DEFINITION_FILE "'...");

  FILE* field_definition_file = fopen(FIELD_DEFINITION_FILE, "r");

  if (field_definition_file == NULL) {
    errorf("Unable to open '" FIELD_DEFINITION_FILE "' (error code %d).", errno);
    tipf("Probably the file doesn't exist.");
    exit(ERROR_OPENING_FIELD_DEFINITION);
  }

  return field_definition_file;
}
static void load_dimensions(FILE* field_definition_file, int* rows, int* columns) {
  fscanf(field_definition_file, "%d %d", rows, columns);
}
static void load_walls(FILE* field_definition_file, int rows, int columns, bool*** walls) {
  *walls = calloc(rows, sizeof(bool*));

  for (int row = 0; row < rows; row++) {
    char row_definition[256];
    fscanf(field_definition_file, "%s", row_definition);

    if (strlen(row_definition) != columns) {
      errorf("Unable to get row %d, expected size %d, but get %lu.", row + 1, columns, strlen(row_definition));
      tipf("Check and fix '" FIELD_DEFINITION_FILE "' at line %d.", row + 2);
      exit(ERROR_READING_ROW_SIZE);
    }

    bool* row_walls = calloc(columns, sizeof(bool));
    for(int column = 0; column < columns; column++) {
      if (row_definition[column] != '.' && row_definition[column] != '#') {
        errorf("Unexpected symbol '%c' at the field definition.", row_definition[column]);
        tipf("Check and fix '" FIELD_DEFINITION_FILE "' at row %d column %d.", row + 2, column + 1);
        exit(ERROR_READING_ROW_SYMBOL);
      }

      row_walls[column] = row_definition[column] == '.';
    }

    (*walls)[row] = row_walls;
  }
}
static void close_field_definition_file(FILE* field_definition_file) {
  fclose(field_definition_file);
}
static void load_field_data(int* rows, int* columns, bool*** walls) {
  FILE* field_definition_file = open_field_definition_file();
  load_dimensions(field_definition_file, rows, columns);
  load_walls(field_definition_file, *rows, *columns, walls);
  close_field_definition_file(field_definition_file);
}

static void solve(game_t* game) {
  logf("Now solving the field...");
  game_solve(game);
  logf("Seems like the field doesn't have any solution...");
}

int main() {
  intro();

  int rows;
  int columns;
  bool** walls;
  load_field_data(&rows, &columns, &walls);

  game_t* game = create_game(rows, columns, walls);

  solve(game);

  destroy_game(game);
}