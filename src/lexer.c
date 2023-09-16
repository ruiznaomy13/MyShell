#include "../inc/minishell.h"
char *is_comma(char *str, char c)
{
    int i;
    char    *new;

    i = 1;
	while (str[i] != c && str[i])
		i++;
    new = ft_substr(str, 1, i - 1);
    return (new);  //  recorremos el array hasta que acabe la ,
}

int    create_token(t_all *all, char *str, int type)
{
    t_token *tkn = NULL;

    tkn = (t_token *)malloc(sizeof(t_token));
    (void)all;
    // Crea el token segun ell tipo de dato que ha encontrado
    if (type == 1)
        tkn->wrd = is_comma(str, str[0]);
    // else if ()
    tkn->type = type;
    printf("TOKEN = %s\n", tkn->wrd);
    return (ft_strlen(tkn->wrd) + 1);
}

void    lexer(t_all *all)
{
    int     i;
    // int    type;

    i = 0;
    while (all->line[i])
    {
        if (all->line[i] == '\"' || all->line[i] == '\'')
        {
            // printf("%d = %s\n", i, &all->line[i]);
            i += create_token(all, &all->line[i], 1);
            printf("%i\n", i);
        }
        else
            i++;
    }
    
}