#pragma once

#include "color.h"

typedef enum {
  PIECE_TYPE_WALL = -2,
  PIECE_TYPE_NONE = -1,
  PIECE_TYPE_F,
  PIECE_TYPE_I,
  PIECE_TYPE_L,
  PIECE_TYPE_N,
  PIECE_TYPE_P,
  PIECE_TYPE_T,
  PIECE_TYPE_U,
  PIECE_TYPE_V,
  PIECE_TYPE_W,
  PIECE_TYPE_X,
  PIECE_TYPE_Y,
  PIECE_TYPE_Z,
  PIECE_TYPE_COUNT
} piece_type_t;

color_t piece_type_get_color(piece_type_t piece_type);