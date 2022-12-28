#pragma once

#include <stdbool.h>
#include "piece.h"

struct field_t;
typedef struct field_t field_t;

field_t* create_field(int rows, int columns);
field_t* create_field_with_walls(int rows, int columns, bool** walls);
void destroy_field(field_t* field);

bool field_cell_is_correct(field_t* field, int row, int column);
bool field_cell_is_free(field_t* field, int row, int column);
void field_cell_find_free(field_t* field, int* row, int* column);
bool field_is_completed(field_t* field);
bool field_wrong_region_exists(field_t* field);
bool field_try_to_put_piece(field_t* field, piece_t* piece, int row, int column);
void field_remove_piece(field_t* field, piece_t* piece, int row, int column);

void draw_field(field_t* field);
void draw_pretty_field(field_t* field);
int field_get_free_region_size(field_t* field, int row, int column);
