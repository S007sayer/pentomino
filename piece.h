#pragma once

#include "piece_types.h"

#define PIECE_BLOCK_COUNT 5

// Отдельный квадратик одного пентамино, его позиция относительно основного (0, 0) блока.
typedef struct {
  int row_offset;
  int column_offset;
} piece_block_t;

// Отдельный кусочек пентамино.
typedef struct {
  piece_type_t type;
  piece_block_t* blocks;
} piece_t;

piece_t* create_piece(piece_type_t type, piece_block_t* blocks);
void destroy_piece(piece_t* piece);