/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:38:26 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/26 21:35:44 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	arg_size(t_token *aux)
{
	int		i;

	i = 0;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == RDOUT || aux->type == RDAP \
			|| aux->type == RDIN || aux->type == RDHD)
			aux = aux->next->next;
		aux = aux->next;
		i++;
	}
	return (i);
}

char    *search_var(char *str)
{
	int i;

	i = 0;
	while (str[++i] && (ft_isalpha(str[i]) || str[i] == '_'));
	return(ft_substr(str, 1, i-1));
}

void    expand_var(t_token *tkn, char **env)
{
	int     i;
	int     flag;
	char    *var;

    i = 0;
    flag = 0;
    var = NULL;
    while (tkn->wrd[i])
    {
        if ((tkn->wrd[i] == '\'' || tkn->wrd[i] == '\"') && flag == 0)
        {
            if (tkn->wrd[i] == '\'')
                flag = COMMA_S;
            else
                flag = COMMA_D;
            i++;
        }
        else if (tkn->wrd[i] == '$' && (flag == 0 || flag == COMMA_D))
        {
            var = search_var(&tkn->wrd[i]);
            tkn->wrd = str_rep(tkn->wrd, ft_strjoin("$", var), search_env(var, env));
            i += ft_strlen(var);
        }
        else
            i++;
    }
}

char **save_arg(t_all *all)
{
	t_token *aux;
	char    **str;
	int     i;

	aux = all->token;
	i = arg_size(aux);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	aux = all->token;
	i = 0;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == RDOUT || aux->type == RDAP \
			|| aux->type == RDIN || aux->type == RDHD)
				aux = aux->next->next;
		if (aux->wrd != NULL)
		{
			expand_var(aux, all->env);
			str[i++] = aux->wrd;
		}
		aux = aux->next;
	}
	str =  quit_comma(str);
	return (str);
}

void	create_process(t_all *all)
{
	int			i;
	t_process	*pcs = NULL;

	i = -1;
	pcs = (t_process *)ft_calloc(sizeof(t_process), 1);//num_process
	if (pcs == NULL)
		return ;
	pcs->process = save_arg(all);
	all->procesos = pcs;
}