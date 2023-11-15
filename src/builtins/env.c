/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:06:16 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/15 21:33:21 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void free_char_array(char **arr)
{
	int	i;

	i = -1;
    if (arr == NULL)
        return;
    while (arr[++i])
        free(arr[i]);
    free(arr);
}

void add_to_env(t_all *all, t_env *env)
{
	t_env	*aux;

	if (all->w_env == NULL)
		all->w_env = env;
	else
	{
		aux = all->w_env;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = env;
	}
}

int	list_env(t_all *all, char **env)
{
	int		i;
	char	**aux;
	t_env	*w_env;

	(void)all;
	i = -1;
	w_env = ft_calloc(sizeof(t_env), 1);
	while (env[++i])
	{
		aux = ft_split(env[i], '=');
		w_env->key = aux[0];
		if (aux[1])
			w_env->value = aux[1];
		if (ft_strchr(env[i], '='))
			w_env->equal = 1;
		free_char_array(aux);
		add_to_env(all, w_env);
	}
	return (0);
}

int ft_env(t_all *all, char **env)
{
    int i;

	(void)all;
    i = -1;
    while (env[++i])
        printf("%s\n", env[i]);
    return (0);
}
