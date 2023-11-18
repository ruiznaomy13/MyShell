/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:49:51 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/18 16:33:28 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_rd(int type)
{
	if (type == RDHD || type == RDIN || type == RDAP || type == RDOUT)
		return (1);
	return (0);
}

void	count_process(t_all *all, char *str)
{
	int	i;
	int	n_proces;

	i = 0;
	n_proces = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			n_proces++;
		i++;
	}
	n_proces += 1;
	all->num_process = n_proces;
}

int ft_arr_len(void **ptr)
{
    int i = 0;
    while (ptr[i])
        i++;
    return (i);
}
