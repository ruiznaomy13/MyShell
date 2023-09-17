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
    if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '$')
        return (1);
    return (0);
}

char    *is_text(char *str)
{
    int i;

    i = 0;
    char    *new;
    if (delimiter(str[i]))
        i++;
    while (!delimiter(str[i]) && str[i])
        i++;
    new = ft_substr(str, 0, i);
    return (new);
}

int    create_token(t_all *all, char *str, int type)
{
    t_token *tkn = NULL;

    tkn = (t_token *)malloc(sizeof(t_token));
    (void)all;
    // Crea el token segun ell tipo de dato que ha encontrado
    if (type == COMMA_S || type == COMMA_D)
        tkn->wrd = is_comma(str, str[0]);
    else if (type == TEXT || type == EXP)
        tkn->wrd = is_text(str);
    else if (type == PIPE)
        tkn->wrd = "|";
    else if (type == RDAP)
        tkn->wrd = ">>";
    else if (type == RDHD)
        tkn->wrd = "<<";
    else if (type == RDOUT)
        tkn->wrd = ">";
    else if (type == RDIN)
        tkn->wrd = "<";
    tkn->type = type;
    printf("TOKEN = %s->TYPE = %d\n", tkn->wrd, type);
    return (ft_strlen(tkn->wrd));
}

void    lexer(t_all *all)
{
    int     i;

    i = -1;
    while (all->line[++i])
    {
        if (all->line[i] == '\'')
            i += create_token(all, &all->line[i], COMMA_S) + 1;
        else if (all->line[i] == '\"')
            i += create_token(all, &all->line[i], COMMA_D) + 1;
        else if (!delimiter(all->line[i]))
            i += create_token(all, &all->line[i], TEXT);
        else if (all->line[i] == '$')
            i += create_token(all, &all->line[i], EXP);
        else if (all->line[i] == '|')
            i += create_token(all, &all->line[i], PIPE);
        else if (all->line[i] == '>' && all->line[i + 1] == '>')
            i += create_token(all, &all->line[i], RDAP);
        else if (all->line[i] == '<' && all->line[i + 1] == '<')
            i += create_token(all, &all->line[i], RDHD);
        else if (all->line[i] == '>')
            i += create_token(all, &all->line[i], RDOUT);
        else if (all->line[i] == '<')
            i += create_token(all, &all->line[i], RDIN);;
    }
}
