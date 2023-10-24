/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:04 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/24 13:03:37 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
int	checker(t_all *all)
{
    if (ft_strlen(all->line) < 1)
        return (0);
    else if (!syntax_checker(all))
    {
        ft_error(5);
        return (0);
    }
    return (1);
}

int syntax_checker(t_all *all)
{
    t_token *aux;

    aux = all->token;
    while (aux != NULL)
    {
        if (aux->type == PIPE && \
		!(aux->next == NULL || aux->next->type == TEXT || is_rd(aux->next->type)))
            return (0);
		else if (is_rd(aux->type) && (aux->next == NULL || aux->next->type != TEXT))
            return (0);
        aux = aux->next;
    }
    return (1);
}

int	check_cometes(char *str)
{
	int		i;
	int		coma;
	int		flag;

	i = 0;
	coma = 0;
	flag = 0;
	if (!str)
		return (0);
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
	if (flag == 1) {
		ft_error(coma);
		return (coma);
	}
	else
		return (flag);
}
