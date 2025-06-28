#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenlist_init(tokenList *tokenList) {
  tokenList->capacity = 10;
  tokenList->count = 0;
  tokenList->tokens = malloc(sizeof(token) * tokenList->capacity);
}
void tokenlist_add(tokenList *tokenList, token token) {
  if (tokenList->count >= tokenList->capacity) {
    tokenList->capacity *= 2;
    tokenList->tokens =
        realloc(tokenList->tokens, sizeof(token) * tokenList->capacity);
  }

  tokenList->count++;
  tokenList->tokens[tokenList->count - 1] = token;
}
void tokenlist_destroy(tokenList *tokenList) { free(tokenList->tokens); };

void lexer_init(lexer *lexer, FILE *fptr) {
  lexer->fptr = fptr;
  lexer->line = 0;
  lexer->cur_char = fgetc(fptr);
  lexer->buf_index = 0;
}
void lexer_advance(lexer *lexer) {
  lexer->cur_char = fgetc(lexer->fptr);

  if (lexer->cur_char == '\n') {
    lexer->line++;
  }
}

void lexer_classify(lexer *lexer, tokenList *tokens) {

  while (lexer->cur_char != EOF) {

    if (isalpha(lexer->cur_char)) {
      lexer->buffer[lexer->buf_index] = lexer->cur_char;
      lexer->buf_index++;
    }

    if (strcmp(lexer->buffer, "return") == 0) {
      token token;
      token.lexeme = "return";
      token.line = lexer->line;
      token.type = RETURN;

      tokenlist_add(tokens, token);

      lexer->buf_index = 0;
      memset(lexer->buffer, '\0', sizeof(lexer->buffer));
    }

    lexer_advance(lexer);
  }
}

void lexer_destroy(lexer *lexer) {
  if (lexer->fptr) {
    fclose(lexer->fptr);
    lexer->fptr = NULL;
  }
}