/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:15:41 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/12 13:42:49 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	count_env_tokens(t_env *env)
{
	t_env	*aux;
	int		count;

	aux = env;
	count = 0;
	while (aux != NULL)
	{
		aux = aux->next;
		count++;
	}
	return (count);
}

void	actualize_env(t_all *all)
{
	int		i;
	char	**env;
	t_env	*x;
	int		total_len;

	((0) || (i = 0) || (total_len = 0));
	x = all->w_env;
	env = ft_calloc(count_env_tokens(all->w_env) + 1, sizeof(char *));
	if (!env)
		return ;
	free_char_array(all->env);
	while (x != NULL)
	{
		total_len = ft_strlen(x->key) + ft_strlen(x->value) + 1;
		env[i] = ft_calloc(total_len, sizeof(char));
		if (!env[i])
			return (free_char_array(env));
		strcpy(env[i], x->key);
		if (x->equal)
			env[i] = ft_charjoin(env[i], '=');
		if (x->value)
			env[i] = ft_strjoin(env[i], x->value);
		x = x->next;
		i++;
	}
	all->env = env;
}
