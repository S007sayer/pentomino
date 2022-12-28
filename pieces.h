#pragma once

#include <stdbool.h>
#include "piece.h"

typedef struct { 
  int piece_count;
  piece_t** pieces;
  bool* used;
  int used_count;
} pieces_t; 

typedef int piece_id_t;

pieces_t* create_pieces();
void destroy_pieces(pieces_t* pieces);

bool pieces_is_used(pieces_t* pieces, piece_id_t piece_id);
void pieces_use(pieces_t* pieces, piece_id_t piece_id);
void pieces_unuse(pieces_t* pieces, piece_id_t piece_id);
