#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int a = 0;
    
    pid = fork();
    if (pid > 0)
    {
        printf("pare\n");
    }
    else if(pid == 0)
    {
        char** aaaaa = calloc(1, sizeof(char*));
        aaaaa[0] = "/home/maria";
        execve("asdfghjkljhgf", aaaaa, NULL);
        exit(0);
        printf("aaaaaaaaaaaaaaaaaaaaaaaa\n");
    }
    else
        printf("cabróooooooooooo");

    wait(NULL);

    printf("hola %d", a);
}