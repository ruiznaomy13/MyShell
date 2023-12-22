/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:15:41 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/22 13:26:09 by ncastell         ###   ########.fr       */
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

void	save_key(char **env, int i, t_env *x)
{
	char	*temp;

	if (!env[i])
	{
		free_char_array(env);
		env[i] = ft_calloc(1, sizeof(char));
	}
	strcpy(env[i], x->key);
	if (x->equal)
	{
		temp = env[i];
		env[i] = ft_charjoin(temp, '=');
		free(temp);
	}
	if (x->value)
	{
		temp = env[i];
		env[i] = ft_strjoin(temp, x->value);
		free(temp);
	}
}

void	actualize_env(t_all *all)
{
	int		i;
	char	**env;
	t_env	*x;
	int		total_len;

	((0) || (i = 0) || (total_len = 0));
	x = all->w_env;
	env = ft_calloc(count_env_tokens(all->w_env) + 2, sizeof(char *));
	if (!env)
		return ;
	free_char_array(all->env);
	while (x != NULL)
	{
		total_len = ft_strlen(x->key) + ft_strlen(x->value) + 1;
		env[i] = ft_calloc(total_len + 1, sizeof(char));
		if (!env[i])
			return (free_char_array(env));
		save_key(env, i, x);
		x = x->next;
		i++;
	}
	env[i] = NULL;
	all->env = env;
}
