/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:00:55 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/23 14:20:23 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	arg_size(t_token *tkn)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = tkn;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == RDOUT || aux->type == RDAP \
			|| aux->type == RDIN || aux->type == RDHD)
			aux = aux->next;
		aux = aux->next;
		i++;
	}
	return (i);
}

void	add_rd(t_token *rd, t_process *pcs)
{
	t_token	*aux;

	if (pcs->rd == NULL)
		pcs->rd = rd;
	else
	{
		aux = pcs->rd;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = rd;
	}
}

void	list_redirection(t_process *pcs, t_all *all)
{
	t_token	*aux;
	t_token	*rd;

	aux = all->token;
	while (aux != NULL && aux->type != PIPE)
	{
		if (is_rd(aux->type))
		{
			rd = (t_token *)ft_calloc(sizeof(t_token), 1);
			if (!rd)
				return ;
			rd->type = aux->type;
			rd->wrd = expand_var(all, aux->next, rd->type);
			add_rd(rd, pcs);
			aux = aux->next;
		}
		aux = aux->next;
	}
}

char	**save_arg(t_all *all)
{
	char	**str;
	char	*str_aux;
	t_token	*aux;
	int		i;

	aux = all->token;
	str = (char **)ft_calloc(sizeof(char *), (arg_size(all->token) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (aux != NULL && aux->type != PIPE)
	{
		if (is_rd(aux->type))
			aux = aux->next;
		else if (aux->wrd != NULL)
		{
			str_aux = expand_var(all, aux, 0);
			str[i++] = ft_strdup(str_aux);
			free(str_aux);
		}
		aux = aux->next;
	}
	str[i] = NULL;
	return (str);
}
