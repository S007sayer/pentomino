#include "pieces.h"

#include <stdlib.h>

pieces_t* create_pieces() {
  pieces_t* pieces = malloc(sizeof(pieces_t));

  pieces->piece_count = 63;
  pieces->pieces = calloc(pieces->piece_count, sizeof(piece_t*));
  pieces->pieces[0] = create_piece(PIECE_TYPE_I, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 } }); 
  pieces->pieces[1] = create_piece(PIECE_TYPE_I, (piece_block_t[4]) { { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 } });
  pieces->pieces[2] = create_piece(PIECE_TYPE_X, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 1, 1 }, { 2, 0 } });
  pieces->pieces[3] = create_piece(PIECE_TYPE_Z, (piece_block_t[4]) { { 0, 1 }, { 1, 0 }, { 2, -1 }, { 2, 0 } });
  pieces->pieces[4] = create_piece(PIECE_TYPE_Z, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 } });
  pieces->pieces[5] = create_piece(PIECE_TYPE_Z, (piece_block_t[4]) { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 2 } });
  pieces->pieces[6] = create_piece(PIECE_TYPE_Z, (piece_block_t[4]) { { 1, -2 }, { 1, -1 }, { 1, 0 }, { 2, -2 } });
  pieces->pieces[7] = create_piece(PIECE_TYPE_V, (piece_block_t[4]) { { 1, 0 }, { 2, 0 }, { 2, 1 }, { 2, 2 } });
  pieces->pieces[8] = create_piece(PIECE_TYPE_V, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 0 }, { 2, 0 } });
  pieces->pieces[9] = create_piece(PIECE_TYPE_V, (piece_block_t[4]) { { 1, 0 }, { 2, -2 }, { 2, -1 }, { 2, 0 } });
  pieces->pieces[10] = create_piece(PIECE_TYPE_V, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 2 }, { 2, 2 } });
  pieces->pieces[11] = create_piece(PIECE_TYPE_T, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 1 }, { 2, 1 } });
  pieces->pieces[12] = create_piece(PIECE_TYPE_T, (piece_block_t[4]) { { 1, -2 }, { 1, -1 }, { 1, 0 }, { 2, 0 } });
  pieces->pieces[13] = create_piece(PIECE_TYPE_T, (piece_block_t[4]) { { 1, 0 }, { 2, -1 }, { 2, 0 }, { 2, 1 } });
  pieces->pieces[14] = create_piece(PIECE_TYPE_T, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 0 } });
  pieces->pieces[15] = create_piece(PIECE_TYPE_W, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 2, 1 }, { 2, 2 } });
  pieces->pieces[16] = create_piece(PIECE_TYPE_W, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 2, -2 }, { 2, -1 } });
  pieces->pieces[17] = create_piece(PIECE_TYPE_W, (piece_block_t[4]) { { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 } });
  pieces->pieces[18] = create_piece(PIECE_TYPE_W, (piece_block_t[4]) { { 0, 1 }, { 1, -1 }, { 1, 0 }, { 2, -1 } });
  pieces->pieces[19] = create_piece(PIECE_TYPE_U, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 2 } });
  pieces->pieces[20] = create_piece(PIECE_TYPE_U, (piece_block_t[4]) { { 0, 1 }, { 1, 1 }, { 2, 0 }, { 2, 1 } });
  pieces->pieces[21] = create_piece(PIECE_TYPE_U, (piece_block_t[4]) { { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } });
  pieces->pieces[22] = create_piece(PIECE_TYPE_U, (piece_block_t[4]) { { 0, 1 }, { 1, 0 }, { 2, 0 }, { 2, 1 } });
  pieces->pieces[23] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 } });
  pieces->pieces[24] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 1, 0 }, { 2, 0 }, { 3, -1 }, { 3, 0 } });
  pieces->pieces[25] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 3 } });
  pieces->pieces[26] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 0, 1 }, { 1, 0 }, { 2, 0 }, { 3, 0 } });
  pieces->pieces[27] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } });
  pieces->pieces[28] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 0 } });
  pieces->pieces[29] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 1, 0 }, { 2, 0 }, { 3, 0 }, { 3, 1 } });
  pieces->pieces[30] = create_piece(PIECE_TYPE_L, (piece_block_t[4]) { { 1, -3 }, { 1, -2 }, { 1, -1 }, { 1, 0 } });
  pieces->pieces[31] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 0, 1 }, { 1, -2 }, { 1, -1 }, { 1, 0 } });
  pieces->pieces[32] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 2, 1 }, { 3, 1 } });
  pieces->pieces[33] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, -1 }, { 1, 0 } });
  pieces->pieces[34] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 1 } });
  pieces->pieces[35] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 0, 1 }, { 1, 1 }, { 1, 2 }, { 1, 3 } });
  pieces->pieces[36] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 1, 0 }, { 2, -1 }, { 2, 0 }, { 3, -1 } });
  pieces->pieces[37] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 2 }, { 1, 3 } });
  pieces->pieces[38] = create_piece(PIECE_TYPE_N, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 2, -1 }, { 3, -1 } });
  pieces->pieces[39] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 1, -2 }, { 1, -1 }, { 1, 0 }, { 1, 1 } });
  pieces->pieces[40] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 2, 0 }, { 3, 0 } });
  pieces->pieces[41] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 1 } });
  pieces->pieces[42] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 0 } });
  pieces->pieces[43] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 2 } });
  pieces->pieces[44] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 2, 0 }, { 3, 0 } });
  pieces->pieces[45] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 1, 1 }, { 1, 2 } });
  pieces->pieces[46] = create_piece(PIECE_TYPE_Y, (piece_block_t[4]) { { 1, 0 }, { 2, -1 }, { 2, 0 }, { 3, 0 } });
  pieces->pieces[47] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 1, 1 }, { 2, 1 } });
  pieces->pieces[48] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 0, 1 }, { 1, -1 }, { 1, 0 }, { 2, 0 } });
  pieces->pieces[49] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 1 } });
  pieces->pieces[50] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 2, -1 }, { 2, 0 } });
  pieces->pieces[51] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 1, -2 }, { 1, -1 }, { 1, 0 }, { 2, -1 } });
  pieces->pieces[52] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 1 } });
  pieces->pieces[53] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 1, 1 }, { 2, -1 } });
  pieces->pieces[54] = create_piece(PIECE_TYPE_F, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 2, 0 }, { 2, 1 } });
  pieces->pieces[55] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 1 } });
  pieces->pieces[56] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 } });
  pieces->pieces[57] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 1, 0 }, { 1, 1 }, { 2, 0 }, { 2, 1 } });
  pieces->pieces[58] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } });
  pieces->pieces[59] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, 2 } });
  pieces->pieces[60] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 1, -1 }, { 1, 0 }, { 2, -1 }, { 2, 0 } });
  pieces->pieces[61] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 0, 1 }, { 0, 2 }, { 1, 1 }, { 1, 2 } });
  pieces->pieces[62] = create_piece(PIECE_TYPE_P, (piece_block_t[4]) { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 0 } });

  pieces->used = calloc(PIECE_BLOCK_COUNT, sizeof(bool));

  return pieces;
}

void destroy_pieces(pieces_t* pieces) {
  for(int i = 0; i < pieces->piece_count; i++) {
    destroy_piece(pieces->pieces[i]);
  } 
  free(pieces->pieces);
  free(pieces);
}

bool pieces_is_used(pieces_t* pieces, piece_id_t piece_id) {
  piece_t* piece = pieces->pieces[piece_id];
  return pieces->used[piece->type];
}
void pieces_use(pieces_t* pieces, piece_id_t piece_id) {
  piece_t* piece = pieces->pieces[piece_id];
  pieces->used[piece->type] = true;
  pieces->used_count++;
}
void pieces_unuse(pieces_t* pieces, piece_id_t piece_id) {
  piece_t* piece = pieces->pieces[piece_id];
  pieces->used[piece->type] = false;
  pieces->used_count--;
}

