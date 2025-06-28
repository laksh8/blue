#ifndef LEXER_H
#define LEXER_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// lexer structure
typedef struct {
  FILE *fptr;
  int line;
  char cur_char;

  char buffer[255];
  int buf_index;
} lexer;

// token structure

typedef enum {
  IDENTIFIER,
  RETURN,
  UNIDENTIFIED,
} tokenType;

typedef struct {
  tokenType type;
  char *lexeme;
  int line;
} token;

typedef struct {
  token *tokens;
  int capacity;
  int count;
} tokenList;

// function declarations
void tokenlist_init(tokenList *tokenList);
void tokenlist_add(tokenList *tokenList, token token);
void tokenlist_destroy(tokenList *tokenList);

void lexer_init(lexer *lexer, FILE *fptr);
void lexer_advance(lexer *lexer);
void lexer_classify(lexer *lexer, tokenList *tokens);
void lexer_destroy(lexer *lexer);

#endif