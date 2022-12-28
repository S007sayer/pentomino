#pragma once

#include <stdbool.h>

struct game_t;
typedef struct game_t game_t;

game_t* create_game(int rows, int columns, bool** walls);
void destroy_game(game_t* game);
void game_solve(game_t* game);
void game_play(game_t* game, int row, int column);
