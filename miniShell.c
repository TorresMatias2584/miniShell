#include "miniShell.h"

int main(int argc, char *argv[])
{
    while (1)
    {
        char *input = malloc(sizeof(char) * 2);
        if (input == NULL)
        {   perror("Malloc");
            return 1;
        }
        input[0] = '\0';
        int c, i = 0;
        printf("~$ ");
        fflush(stdout);
        while ((c = fgetc(stdin)) != '\n' && c != EOF) // bucle para el ingreso de comandos
        {
            char *aux = realloc(input, sizeof(char) * (i + 2));
            if (aux == NULL)
            {
                perror("Realloc");
                free(input);
                return 1;
            }
            input = aux;
            input[i] = (char)c;
            input[i + 1] = '\0';
            i++;
        }

        if (c == EOF || !strcmp(input, "exit"))
        { // comando para salir del miniShell
            free(input);
            break;
        }

        TokenList *command = tokenizador(input);
        if(command == NULL || command->contador == 0){
            free(command);
            free(input);
            continue;
        } 

        pid_t ID = fork(); // crea un proceso hijo para que maneje el comando ingresado.
        if(ID < 0)
        {   
            perror("Fork");
        }

        else if (ID == 0) // si es el hijo hace esto...     (execvp)
        {
            char **args = malloc(sizeof(char*) * (command->contador + 1));
            if (args == NULL) {
                perror("Malloc");
                free_token_list(*command);
                free(command);
                free(input);
                exit(1);
            }
            
            int n = 0;
            for(int i = 0; i < command->contador; i++)
            {
                if(command->items[i].type == TOKEN_WORD)    args[n++] = command->items[i].palabra;
            }
            args[n] = NULL;

            execvp(args[0],args);

            free_token_list(*command);
            free(command);
            free(input);
            exit(0); // para devolverle el poder al padre
        }

        else{
            int estadoDelProcesoHijo;  // estado en el que volvio el hijo.
            waitpid(ID, &estadoDelProcesoHijo,0); // el proceso padre se bloquea esperando la finalizacion del hijo
            printf("El hijo ya volvio. \n");
        }
        
        free_token_list(*command);
        free(command);
        free(input);
    }

    printf("Terminal Cerrada.\n");
    return 0;
}