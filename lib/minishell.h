#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include "../lib/libft/libft.h"

typedef struct s_token
{
    int             type;
    char            *wrd;
    int             len;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_all
{
    char    *line;
    int     size;
    // char    **env;
    t_token *token;
}   t_all;

#endif