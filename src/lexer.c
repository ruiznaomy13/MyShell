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

int delimiter(char c)
{
    if (c == '>' || c == '<' || c == '|' || c == ' ')
        return (1);
    return (0);
}

char    *is_text(char *str)
{
    int i;

    i = 0;
    char    *new;
    printf("entro\n");
    while (!delimiter(str[i]) && str[i])
        i++;
    printf("index when text = %d\n", i);
    new = ft_substr(str, 0, i);
    return (new);
}

int    create_token(t_all *all, char *str, int type)
{
    t_token *tkn = NULL;

    tkn = (t_token *)malloc(sizeof(t_token));
    (void)all;
    // Crea el token segun ell tipo de dato que ha encontrado
    if (type == TEXT)
        tkn->wrd = is_text(str);
    else if (type == PIPE)
        tkn->wrd = "|";
    else if (type == COMMA_S || type == COMMA_D)
        tkn->wrd = is_comma(str, str[0]);
    else if (type == BIG_2)
        tkn->wrd = ">>";
    else if (type == LITTLE_2)
        tkn->wrd = "<<";
    else if (type == BIG)
        tkn->wrd = ">";
    else if (type == LITTLE)
        tkn->wrd = "<";
    tkn->type = type;
    printf("TOKEN = %s\n", tkn->wrd);
    return (ft_strlen(tkn->wrd));
}

void    lexer(t_all *all)
{
    int     i;

    i = 0;
    while (all->line[i])
    {
        if (!delimiter(all->line[i]))
            i += create_token(all, &all->line[i], TEXT);
        else if (all->line[i] == '|')
            i += create_token(all, &all->line[i], PIPE);
        else if (all->line[i] == '\'')
            i += create_token(all, &all->line[i], COMMA_S) + 2;
        else if (all->line[i] == '\"')
            i += create_token(all, &all->line[i], COMMA_D) + 2;
        else if (all->line[i] == '>' && all->line[i + 1] == '>')
            i += create_token(all, &all->line[i], BIG_2);
        else if (all->line[i] == '<' && all->line[i + 1] == '<')
            i += create_token(all, &all->line[i], LITTLE_2);
        else if (all->line[i] == '>')
            i += create_token(all, &all->line[i], BIG);
        else if (all->line[i] == '<')
            i += create_token(all, &all->line[i], LITTLE);
        else
            i++;
    }
}