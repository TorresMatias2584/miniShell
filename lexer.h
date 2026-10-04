
#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_EOF // Fin de la línea
} TokenType;

typedef struct {
    TokenType type;
    char *value; // El texto real (ej: "ls") (se reserva con malloc)
} Token;

#endif