/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:04 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/31 15:31:59 by mmonpeat         ###   ########.fr       */
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
	t_token	*a;
	int		flag;

	flag = 0;
	a = all->token;
	if (a->type == PIPE)
		return (ft_error(all, SYNTAX_ERROR, a->wrd));
	while (a != NULL)
	{
		if (a->type == PIPE && \
		(a->next == NULL || (a->next->type != TEXT \
		&& !is_rd(a->next->type))))
			return (free_token_list(all->token), \
			ft_error(all, SYNTAX_ERROR, a->wrd));
		else if (is_rd(a->type) && (a->next == NULL \
			|| a->next->type != TEXT))
			return (free_token_list(all->token), \
			ft_error(all, SYNTAX_ERROR, a->wrd));
		a = a->next;
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
