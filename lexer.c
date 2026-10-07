#include "lexer.h"

TokenList *tokenizador(char *input)
{
    int cantidad = 10;
    TokenList *tokens = malloc(sizeof(TokenList));
    if(tokens == NULL)
    {
        fprintf(stderr,"Malloc(Tokenizador).");
        return tokens;
    }

    tokens->contador = 0;
    tokens->items = malloc(cantidad * sizeof(Token));
    if (tokens->items == NULL)
    {
        fprintf(stderr, "Malloc(items)\n");
        free(tokens);
        return NULL;
    }

    // Iteramos entre los caracteres mientras no se llegue al final del string
    int i = 0;
    while (input[i] != '\0') 
    {
        // omitimos los espacios en blanco
        if (input[i] == 32)
        { 
            i++;
            continue;
        }

        // aumentamos la cantidad de tokens guardables de forma dinamica
        if (tokens->contador >= cantidad) 
        {
            cantidad += 5;
            void *aux = realloc(tokens->items, sizeof(Token) * cantidad);
            if (aux == NULL)
            {
                fprintf(stderr,"Realloc");
                free_token_list(*tokens);
                free(tokens);
                return NULL;
            }
            tokens->items = aux;
        }

        // detectar tokens
        if(clasificadorTipos(&tokens->items[tokens->contador],input,&i)) // revisa si es del tipo '|', '>', '<', '>>'.
        {
            tokens->contador++;
            i++;
            continue;
        }
        int inicio = i;
        int fin;
        if(input[i] == 34)
        {   
            while(input[++i] != 34)
            {
                if(input[i] == '\0')
                {
                    fprintf(stderr,"No se cerraron las comillas dobles \n");
                    free_token_list(*tokens);
                    free(tokens);
                    return NULL;
                }
            }
            fin = i;
            inicio++;
            i++;
        }
        else if(input[i] == 39)
        {   
            while(input[++i] != 39)
            {
                if(input[i] == '\0')
                {
                    fprintf(stderr,"No se cerro la comilla simple. \n");
                    free_token_list(*tokens);
                    free(tokens);
                    return NULL;
                }
            }
            fin = i;
            inicio++;
            i++;
        }
        else
        {   // detectar palabras
            
            while(input[i] != 32 && !esOperador(input[i]) && input[i] != '\0') 
            {   
                i++;
            }
            fin = i;
        }

        char *auxiliar = malloc(sizeof(char)*(fin - inicio + 1));
        if(auxiliar == NULL)
        {
            fprintf(stderr,"Malloc. \n");
            free_token_list(*tokens);
            free(tokens);
            return NULL;   
        }
        for(int j = 0; j < fin - inicio; j++)
        {
            auxiliar[j] = input[inicio + j];
        }
        auxiliar[fin - inicio] = '\0';
        tokens->items[tokens->contador].type = TOKEN_WORD;
        tokens->items[tokens->contador].palabra = auxiliar;
        tokens->contador++;
    }

    printf("cantidad de tokens: %d \n", tokens->contador);
    //mostrarTokens(tokens); // funcion para corroborar el correcto funcionamiento 
    return tokens;
}

// Función de liberación actualizada
void free_token_list(TokenList list)
{
    for (int i = 0; i < list.contador; i++)
    {
        if (list.items[i].palabra != NULL && list.items[i].type == TOKEN_WORD)
        {
            free(list.items[i].palabra);
        }
    }
    free(list.items);
}

int clasificadorTipos(Token *token, char *input, int *i)
{
    switch (input[*i])
    {
    case '|':
        if (input[*i + 1] == '|')
        {
            token->palabra = "||";
            token->type = TOKEN_OR;
            (*i)++;
        }
        else
        {
            token->palabra = "|";
            token->type = TOKEN_PIPE;
        }
        break;
    case '<':
        if (input[*i + 1] == '<')
        {
            token->palabra = "<<";
            token->type = TOKEN_HERE_DOC;
            (*i)++;
        }
        else
        {
            token->palabra = "<";
            token->type = TOKEN_REDIRECT_IN;
        }
        break;
    case '>':
        if (input[*i + 1] == '>')
        {
            token->palabra = ">>";
            token->type = TOKEN_APPEND;
            (*i)++;
        }
        else
        {
            token->palabra = ">";
            token->type = TOKEN_REDIRECT_OUT;
        }
        break;
    case '&':
        if (input[*i + 1] == '&')
        {
            token->palabra = "&&";
            token->type = TOKEN_AND;
            (*i)++;
        }
        else
        {
            token->palabra = "&";
            token->type = TOKEN_AMPERSAND;
        }
        break;
    default:
        return 0; //  falso
    }
    return 1; // verdadero
}

void mostrarTokens (TokenList *tokens){
    for(int i = 0; i < tokens->contador; i++)
    {
        printf("%s \n",tokens->items[i].palabra);
    }
}

int esOperador(char c)
{   
    if(c == '|' || c == '>' || c == '<' || c == 34 || c == 39 || c== '&'){
        return 1;
    }
    return 0;
}