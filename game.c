#include "game.h"

#include <stdlib.h>
#include <stdio.h>
#include "field.h"
#include "logger.h"
#include "piece.h"
#include "piece_types.h"
#include "pieces.h"

// Terminology.
// - Field - is a game board with surface of 60.
// - Cell - is a single place on field.
// - Region - is a group of cells.
// - Piece - is a single pentomino piece.
// - Block - is a single pentomino part. One pentomino consists of 5 blocks.

// Все использованные пентамино.

struct game_t { 
  bool running;
  field_t* field;
  pieces_t* pieces;
};

game_t* create_game(int rows, int columns, bool** walls) {
  game_t* game = malloc(sizeof(game_t));

  game->running = true;
  game->field = create_field_with_walls(rows, columns, walls);
  game->pieces = create_pieces();

  return game;
}
void destroy_game(game_t* game) {
  destroy_field(game->field);
  destroy_pieces(game->pieces);
  free(game);
}

void game_stop(game_t* game) {
  game->running = false;
}

void game_solve(game_t* game) {
  int row;
  int column;
  field_cell_find_free(game->field, &row, &column);
  game_play(game, row, column);
}
void game_play(game_t* game, int row, int column) {
  pieces_t* pieces = game->pieces;
  field_t* field = game->field;

  for (int piece_id = 0; piece_id < pieces->piece_count; piece_id++) {
    if (!pieces_is_used(pieces, piece_id)) {
      piece_t* piece = pieces->pieces[piece_id];
      if (!field_try_to_put_piece(field, piece, row, column)) {
        continue;
      }
      //draw_field(field);
      if (field_wrong_region_exists(field)) {
        field_remove_piece(field, piece, row, column);
        continue;
      }

      pieces_use(pieces, piece_id);

      if (field_is_completed(field) || pieces->used_count == PIECE_TYPE_COUNT) {
        draw_pretty_field(field);
        destroy_game(game);
        exit(0);
      } else {
        int next_row = row;
        int next_column = column;

        // while()
        game_play(game, next_row, next_column);
        while (!field_cell_is_free(field, next_row, next_column)) {
          next_column++;
          if (!field_cell_is_correct(field, next_row, next_column)) {
            next_column = 0;
            next_row++;

            if (!field_cell_is_correct(field, next_row, next_column)) {
              return;
            }
          }
        }
        game_play(game, next_row, next_column);
      }
      field_remove_piece(field, piece, row, column);
      pieces_unuse(pieces, piece_id);
    }
  }

  // if (field_cell_is_correct(field, next_row, next_column)) {
  //   int next_row = row;
  //   int next_column = column;
  //   do {
  //     next_column++;
  //     if (!field_cell_is_correct(field, next_row, next_column)) {
  //       next_column = 0;
  //       next_row++;
  //       if (!field_cell_is_correct(field, next_row, next_column)) {
  //         return;
  //       }
  //     }
  //   } while (!field_cell_is_free(field, next_row, next_column));
  //   game_play(game, next_row, next_column);  // and try to complete the solution
  // }
}