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
  EOS,
  COMMA,
  LBRACKET,
  RBRACKET,
  INT,
  PLUS,
  MINUS,
  IF,
  GOTO,
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
token token_classify(lexer *lexer);
token token_construct(token *token, char *lexeme, tokenType type, int line);
char *tokentype_get(token *token);

void lexer_init(lexer *lexer, FILE *fptr);
void lexer_advance(lexer *lexer);
char lexer_peek(lexer *lexer);
int lexer_delimscmp(char nextChar);
void lexer_classify(lexer *lexer, tokenList *tokens);
void lexer_destroy(lexer *lexer);
void lexer_cleanup(lexer *lexer);

#endif