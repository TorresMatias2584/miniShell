#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "miniShell.h"
#include <sys/wait.h>

typedef enum
{
    TOKEN_WORD,         // palabras (ls, mkdir, etc.)
    TOKEN_PIPE,         // '|'
    TOKEN_REDIRECT_IN,  // '>'
    TOKEN_REDIRECT_OUT, // '<'
    TOKEN_APPEND,       // '>>'
    TOKEN_EOF           // Fin de la línea
} TokenType;

typedef struct
{
    TokenType type; // tipo de token
    char *palabra;    // El texto real (ej: "ls") (se reserva con malloc)
} Token;

typedef struct
{
    Token *items; // puntero a array dinamico de tokens
    int contador; // contador de tokens
} TokenList;

// devuelve un puntero a una lista de tokens. La lista se compone en los items de tokens y un contador de tokens. Un token tiene tipo y el texto de dicho token.
TokenList *tokenizador(char *input);

void free_token_list(TokenList list);

int clasificadorTipos(Token *token, char *input, int *i);

void mostrarTokens (TokenList *tokens);

#endif