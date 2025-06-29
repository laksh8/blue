#include "lexer.h"
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

  lexer lexer;
  tokenList tokens;
  tokenlist_init(&tokens);

  lexer_init(&lexer, fptr);
  lexer_classify(&lexer, &tokens);

  for (int i = 0; i < tokens.count; i++) {
    token curtoken = tokens.tokens[i];
    token token1 = tokens.tokens[0];
    printf("line - %d | type - %s | lexeme - %s\n", curtoken.line,
           token_getstring(curtoken.type), curtoken.lexeme);
  }

  lexer_destroy(&lexer);
  tokenlist_destroy(&tokens);

  return 0;
}
