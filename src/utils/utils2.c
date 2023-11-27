/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:49:51 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/30 16:24:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_rd(int type)
{
	if (type == RDHD || type == RDIN || type == RDAP || type == RDOUT)
		return (1);
	return (0);
}


char	*split_env(char *str)//entenc que es per l'expansor
{
	int		j;
	char	**sep;
	char	*value;

	sep = ft_split(str, '=');
	if (sep != NULL)
	{
		value = ft_strdup(sep[1]);
		j = -1;
		while (sep[++j] != NULL)
			free(sep[j]);
		free(sep);
		return (value);
	}
	return (NULL);
}

int ft_arr_len(void **ptr)
{
    int i = 0;
    while (ptr[i])
        i++;
    return (i);
}