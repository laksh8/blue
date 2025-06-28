#include "utils.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_error(const char *message) {
  fprintf(stderr, "Error: %s\n%d\n", message, errno);
}
