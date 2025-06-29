#include "lexer.h"
#include <errno.h>
#include <stdio.h>

void log_error(const char *message);
void log_unidentified_token(int line, char *buffer);
