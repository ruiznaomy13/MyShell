/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:06:16 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/16 20:25:40 by ncastell         ###   ########.fr       */
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
	t_env	*aux_env;

	(void)all;
	i = -1;
	while (env[++i])
	{
		aux_env = ft_calloc(sizeof(t_env), 1);
		if (!aux_env)
			return (-1);
		aux = ft_split(env[i], '=');
		aux_env->key = strdup(aux[0]);
		if (aux[1])
			aux_env->value = strdup(aux[1]);
		if (ft_strchr(env[i], '='))
			aux_env->equal = 1;
		aux_env->next = NULL;
		add_to_env(all, aux_env);
		free_char_array(aux);
	}
	return (0);
}

int	ft_env(t_all *all)
{
	t_env	*aux;

	aux = all->w_env;
	while (aux != NULL)
	{
		printf("%s", aux->key);
		if (aux->equal)
			printf("=");
		if (aux->value)
			printf("%s", aux->value);
		printf("\n");
		aux = aux->next;
	}
	return (0);
}
