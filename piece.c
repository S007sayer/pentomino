#include "piece.h"

#include <stdlib.h>
#include <string.h>

piece_t* create_piece(piece_type_t type, piece_block_t* blocks) {
  piece_t* piece = malloc(sizeof(piece_t));

  piece->type = type;
  piece->blocks = calloc(PIECE_BLOCK_COUNT - 1, sizeof(piece_block_t));
  memcpy(piece->blocks, blocks, sizeof(piece_block_t[PIECE_BLOCK_COUNT - 1]));

  return piece;
}
void destroy_piece(piece_t* piece) {
  free(piece->blocks);
  free(piece);
}