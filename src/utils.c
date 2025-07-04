#include "utils.h"
#include <errno.h>
#include <stdio.h>

void log_error(const char *message) {
  fprintf(stderr, "Error: %s\n%d\n", message, errno);
}
void log_unidentified_token(int line, char *buffer) {
  fprintf(stderr, "Error: Unidentified token %s at line %d\n%d\n", buffer, line,
          errno);
}
