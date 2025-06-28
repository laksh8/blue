#include "utils.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    log_error("Incorrect usage\nCorrect usage: blue path/to/input.blue");
    return 1;
  }

  FILE *fptr = fopen(argv[1], "r");

  if (fptr == NULL) {
    log_error("Couldn't open file");
    return 1;
  }

  return 0;
}
