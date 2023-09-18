#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define TEXT 00
# define PIPE 01
# define COMMA_S 21
# define COMMA_D 22
# define RDOUT 31
# define RDAP 32
# define RDIN 41
# define RDHD 42
# define EXP 05

typedef struct s_token
{
    int             type;
    char            *wrd;
    // int             len;
    struct s_token  *next;
    // struct s_token  *prev;
}   t_token;

typedef struct s_all
{
    char    *line;
    int     size;
    // char    **env;
    t_token *token;
}   t_all;

void    start_all(t_all *all);
void    lexer(t_all *all);
int     create_token(t_all *all, char *str, int type);
char    *is_comma(char *str, char c);
#endif