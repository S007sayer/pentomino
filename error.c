#include "error.h"

#include <stdlib.h>

void fatal(error_t error) {
  exit(error);
}