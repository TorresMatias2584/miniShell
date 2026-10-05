#include "miniShell.h"

int main(int argc, char *argv[])
{

    while (1)
    {
        char *input = malloc(sizeof(char) * 2);
        if (input == NULL)
            return -1;
        int c, i = 0;
        printf("~$ ");
        while ((c = fgetc(stdin)) != '\n' && c != EOF) // bucle para el ingreso de comandos
        {
            char *aux = realloc(input, sizeof(char) * (i + 2));
            if (aux == NULL)
            {
                free(input);
                return -1;
            }
            input = aux;
            input[i] = (char)c;
            input[i + 1] = '\0';
            i++;
        }
        if (!strcmp(input, "exit"))
        { // comando para salir del miniShell
            free(input);
            return 1;
        }

        int ID = fork(); // crea un proceso hijo para que maneje el comando ingresado.
        if (ID == 0) // si es el hijo hace esto...
        {
            TokenList *command = tokenizador(input);
            exit(0);
        }
        else{
            int estadoDelProcesoHijo;  // estado en el que volvio el hijo.
            waitpid(ID, &estadoDelProcesoHijo,0); // el proceso padre se bloquea esperando la finalizacion del hijo
            printf("El hijo ya volvio. \n");
        }

        free(input);
    }
    return 0;
}