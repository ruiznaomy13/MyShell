/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:49:51 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/27 17:22:43 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_rd(int type)
{
	if (type == RDHD || type == RDIN || type == RDAP || type == RDOUT)
		return (1);
	return (0);
}

int	verify_rep_value(t_env *env, const char *str)
{
	int 	i;
	char 	*str_aux;
	char 	*aux;
	t_env	*node_iter;

	i = -1;
	node_iter = env;
	str_aux = ft_strdup(str);
	aux = NULL;
	if (str_aux == NULL)
		return (-1);
	while (node_iter)
	{
		if (!ft_strcmp(node_iter->key, str_aux))
		{
			free(str_aux);
			return (1);
		}
		node_iter = node_iter->next;
	}
	free(str_aux);
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

char	*rm_value(const char *str, char character)
{
    const char	*found;
	size_t		length;
	char		*newStr;
	
	found = ft_strchr(str, character);
    if (found == NULL)
    	return strdup(str);
	length = found - str;
	newStr = ft_calloc(length + 1, sizeof(char));
	if (!newStr)
		return (NULL);
	ft_strncpy(newStr, str, length);
	newStr[length] = '\0';
	return (newStr);
}
