#include "lexer.h"
#include "utils.h"
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

token token_classify(lexer *lexer) {
  token token;

  char *buffer = strdup(lexer->buffer);

  tokenType tk;

  int line = lexer->line;
  if (lexer->cur_char == '\n') {
    line--;
  }

  if (strcmp(buffer, "return") == 0)
    tk = RETURN;
  else if (strcmp(buffer, ";") == 0)
    tk = EOS;
  else if (strcmp(buffer, ",") == 0)
    tk = COMMA;
  else if (strcmp(buffer, "(") == 0)
    tk = LBRACKET;
  else if (strcmp(buffer, ")") == 0)
    tk = RBRACKET;
  else if (strcmp(buffer, "int") == 0)
    tk = INT;
  else if (strcmp(buffer, "+") == 0)
    tk = PLUS;
  else if (strcmp(buffer, "-") == 0)
    tk = MINUS;
  else if (strcmp(buffer, "if") == 0)
    tk = IF;
  else if (strcmp(buffer, "goto") == 0)
    tk = GOTO;
  else {
    log_unidentified_token(line, buffer);
    exit(1);
  }

  token_construct(&token, buffer, tk, line);

  lexer_cleanup(lexer);

  return token;
}

token token_construct(token *token, char *lexeme, tokenType type, int line) {
  token->lexeme = lexeme;
  token->line = line;
  token->type = type;
}
void lexer_init(lexer *lexer, FILE *fptr) {
  lexer->fptr = fptr;
  lexer->line = 0;
  lexer->cur_char = fgetc(fptr);
  lexer_cleanup(lexer);
}
void lexer_advance(lexer *lexer) {
  lexer->cur_char = fgetc(lexer->fptr);

  if (lexer->cur_char == '\n') {
    lexer->line++;
  }
}

char lexer_peek(lexer *lexer) {
  char next_char = fgetc(lexer->fptr);
  ungetc(next_char, lexer->fptr);
  return next_char;
}

int lexer_delimscmp(char nextChar) {
  char delims[5] = {',', '(', ')', ';', '\n'};

  for (int i = 0; i < 5; i++) {
    if (nextChar == delims[i]) {
      return 1;
    }
  }
  return 0;
}

void lexer_classify(lexer *lexer, tokenList *tokens) {

  while (lexer->cur_char != EOF) {

    if (isspace(lexer->cur_char)) {
      lexer_advance(lexer);
      continue;
    }

    char nextChar = lexer_peek(lexer);
    char curChar = lexer->cur_char;

    if (lexer_delimscmp(curChar)) {
      lexer->buffer[lexer->buf_index] = curChar;
      tokenlist_add(tokens, token_classify(lexer));
    } else if (isspace(nextChar) || lexer_delimscmp(nextChar) ||
               nextChar == '\n') {
      lexer->buffer[lexer->buf_index] = curChar;
      tokenlist_add(tokens, token_classify(lexer));
    } else if (lexer->cur_char != '\n') {
      lexer->buffer[lexer->buf_index] = curChar;
      lexer->buf_index++;
    }

    lexer_advance(lexer);
  }

  if (lexer->buf_index != 0) {
    tokenlist_add(tokens, token_classify(lexer));
  }
}

void lexer_cleanup(lexer *lexer) {
  lexer->buf_index = 0;
  memset(lexer->buffer, '\0', sizeof(lexer->buffer));
}

void lexer_destroy(lexer *lexer) {
  if (lexer->fptr) {
    fclose(lexer->fptr);
    lexer->fptr = NULL;
  }
}