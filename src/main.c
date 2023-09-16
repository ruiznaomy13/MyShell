#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
    t_all   all;

    (0 || (ac = 0) || (av = 0) || (env = 0));
    start_all(&all);
    while (42)
    {
        all.line = readline("myshell🌞> ");
        add_history(all.line);
        printf("%s\n", all.line);
        lexer(&all);
    }
    return (0);
}

void start_all(t_all *all)
{
    all->line = NULL;
    all->token = NULL;
    all->size = 0;
}