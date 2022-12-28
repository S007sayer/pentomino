#include "piece_types.h"

color_t piece_type_get_color(piece_type_t piece_type) {
  if (piece_type == PIECE_TYPE_F)
    return BG_COLOR_YELLOW;
  else if (piece_type == PIECE_TYPE_I)
    return BG_COLOR_RED;
  else if (piece_type == PIECE_TYPE_L)
    return BG_COLOR_YELLOW;
  else if (piece_type == PIECE_TYPE_N)
    return BG_COLOR_GREEN;
  else if (piece_type == PIECE_TYPE_P)
    return BG_COLOR_GREEN;
  else if (piece_type == PIECE_TYPE_T)
    return BG_COLOR_CYAN;
  else if (piece_type == PIECE_TYPE_U)
    return BG_COLOR_CYAN;
  else if (piece_type == PIECE_TYPE_V)
    return BG_COLOR_BLUE;
  else if (piece_type == PIECE_TYPE_W)
    return BG_COLOR_BLUE;
  else if (piece_type == PIECE_TYPE_X)
    return BG_COLOR_MAGENTA;
  else if (piece_type == PIECE_TYPE_Y)
    return BG_COLOR_MAGENTA;
  else if (piece_type == PIECE_TYPE_Z)
    return BG_COLOR_RED;
  else 
    return BG_COLOR_NORMAL;
}