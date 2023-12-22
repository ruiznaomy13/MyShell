/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:04 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/22 13:04:10 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	checker(t_all *all)
{
	if (ft_strlen(all->line) < 1 || !all->token)
		return (1);
	else if (syntax_checker(all))
		return (1);
	return (0);
}

int	syntax_checker(t_all *all)
{
	t_token	*aux;
	int		flag;

	flag = 0;
	aux = all->token;
	while (aux != NULL)
	{
		if (aux->type == PIPE && \
		(aux->next == NULL || (aux->next->type != TEXT \
		&& !is_rd(aux->next->type))))
			return (ft_error(all, SYNTAX_ERROR, aux->wrd));
		else if (is_rd(aux->type) && (aux->next == NULL \
			|| aux->next->type != TEXT))
			return (ft_error(all, SYNTAX_ERROR, aux->wrd));
		aux = aux->next;
	}
	return (0);
}

int	check_cometes(t_all *all, char *str)
{
	int		i;
	int		coma;
	int		flag;

	((0) || (i = 0) || (coma = 0) || (flag = 0));
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag == 0)
		{
			coma = str[i];
			flag = 1;
		}
		else if (coma == str[i] && flag == 1)
			flag = 0;
		i++;
	}
	if (flag == 1)
	{
		if (coma == '"')
			ft_error(all, SYNTAX_ERROR, "\"");
		else
			ft_error(all, SYNTAX_ERROR, "'");
		return (coma);
	}
	return (flag);
}
