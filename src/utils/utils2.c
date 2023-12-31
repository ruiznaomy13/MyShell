/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:49:51 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/31 13:33:07 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	is_rd(int type)
{
	if (type == RDHD || type == RDIN || type == RDAP || type == RDOUT)
		return (1);
	return (0);
}

int	verify_rep_value(t_env *env, const char *str)
{
	int		i;
	char	*str_aux;
	char	*aux;
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

int	ft_arr_len(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	aux_asign_var(char *var, char **aux, char *ita)
{
	free(ita);
	free(var);
	free(*aux);
}
