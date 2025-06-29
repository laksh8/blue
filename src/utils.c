#include "utils.h"
#include "lexer.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_error(const char *message) {
  fprintf(stderr, "Error: %s\n%d\n", message, errno);
}
void log_unidentified_token(int line, char *buffer) {
  fprintf(stderr, "Error: Unidentified token %s at line %d\n%d\n", buffer, line,
          errno);
}

char *tokentype_get(token *token) {
  tokenType tk = token->type;

  switch (tk) {
  case RETURN:
    return "return";
  case EOS:
    return "eos";
  case IDENTIFIER:
    return "identifier";
  case COMMA:
    return "comma";
  case RBRACKET:
    return "rbracket";
  case LBRACKET:
    return "lbracket";
  case INT:
    return "int";
  case PLUS:
    return "plus";
  case MINUS:
    return "minus";
  case IF:
    return "if";
  case GOTO:
    return "goto";

  default:
    return "undefined";
  }
}
