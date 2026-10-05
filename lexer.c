#include "lexer.h"

TokenList *tokenizador(char *input)
{
    int cantidad = 2;
    TokenList *tokens;
    tokens->contador = 0;
    tokens->items = malloc(cantidad * sizeof(tokens));

    int i = 0;
    while (input[i] != '\0') // mientras no se llegue al final del string
    {
        if (input[i] != 32)
        { // omitimos los espacios en blanco
            i++;
            continue;
        }

        if (tokens->contador >= cantidad) // aumentamos la cantidad de tokens guardables de forma dinamica
        {
            cantidad += 5;
            void *aux = realloc(tokens->items, sizeof(tokens) * cantidad);
            if (aux == NULL)
            {
                tokens->contador = -1;
                // free_token_list(tokens);
                return tokens;
            }
            tokens->items = aux;
        }

        if(clasificadorTipos(&tokens->items[tokens->contador],input[i]))
        {   
            tokens->contador++; 
            i++; 
            continue;
        }

        // detectar las palabras. 
        
    }
    
    return tokens;
}

// Función de liberación actualizada
void free_token_list(TokenList list)
{
    for (int i = 0; i < list.contador; i++)
    {
        if (list.items[i].palabra != NULL)
        {
            free(list.items[i].palabra);
        }
    }
    free(list.items);
}

int clasificadorTipos(Token *token,char caracter){
    switch (caracter)
    {
    case '|':
        token->palabra = "|";
        token->type = TOKEN_PIPE;
        break;
    case '<':
        token->palabra = "<";
        token->type = TOKEN_REDIRECT_OUT;
        break;
    case '>':
        token->palabra = ">";
        token->type = TOKEN_REDIRECT_IN;
        break;
    case '>>':
        token->palabra = ">>";
        token->type = TOKEN_APPEND;
        break;
    default:
        return 0;   //  falso
    }
    return 1;   // verdadero
}