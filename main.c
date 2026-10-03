#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  
    while(1){ 
        char *stream = malloc(sizeof(char)*2);
        if(stream == NULL) return -1;
        int c, i = 0;
        printf("~$ ");
        while((c = fgetc(stdin)) != '\n' && c != EOF) // bucle para el ingreso de comandos
        {   
            char* aux = realloc(stream,sizeof(char)*(i+2));
            if(aux == NULL){
                free(stream);
                return -1; }
            stream = aux;
            stream[i] = (char)c;
            stream[i+1] = '\0';
            i++;
        }
        int fd = fork();
        if(fd == 0){
            printf("Soy el proceso hijo con fd = %d y el de mi padre es : %d",getpid(),getppid());
        }
        printf("%s \n",stream);
        free(stream);
    }

    return 0;
}