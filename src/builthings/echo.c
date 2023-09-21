#include "inc/minishell.h"

// char **construct_cmd_argv(s_token)
// {
//     // Hacer un malloc con el numero de tokens + 1
// }

int echo(char **argv)
{
    int i;
    i = 1;
    while(argv[i]){
        printf("%s", argv[i]);
        i++;
    }
    return (0);
}
