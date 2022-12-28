#pragma once

#include <stdio.h>
#include "color.h"

#define logf(...) \
  do { \
    printf("[" FG_COLOR_BLUE "Pentomino" FG_COLOR_NORMAL "] " __VA_ARGS__); \
    printf("\n"); \
  } while (0)
#define errorf(...) \
  do { \
    logf(FG_COLOR_RED "Error: " FG_COLOR_NORMAL __VA_ARGS__); \
  } while (0)
#define tipf(...) \
  do { \
    logf(FG_COLOR_CYAN "Tip: " FG_COLOR_NORMAL __VA_ARGS__); \
  } while (0)