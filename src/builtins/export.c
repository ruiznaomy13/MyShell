/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/27 19:36:55 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	show_exp(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux != NULL)
	{
		printf("declare -x %s", aux->key);
		if (aux->equal)
			printf("=");
		if (aux->value)
			printf("%s", aux->value);
		printf("\n");
		aux = aux->next;
	}
	return (0);
}

int	save_var_env(const char *src, t_all *all)
{
	char	**dup_src;
	t_env	*aux_env;

	dup_src = ft_split(src, '=');
	if (!dup_src)
		return (-1);
	aux_env = ft_calloc(1, sizeof(t_env));
	if (!aux_env)
		return (free(dup_src), -1);
	aux_env->key = ft_strdup(dup_src[0]);
	if (ft_strchr(src, '='))
		aux_env->equal = 1;
	if(dup_src[1])
		aux_env->value = ft_strdup(dup_src[1]);
	else
		aux_env->value = NULL;
	add_to_env(all, aux_env);
	free_char_array(dup_src);
	return (0);
}

int	check_var(t_env *w_env, char *str)
{
	char	*aux;

	aux = rm_value(str, '=');
	printf("STR == %s\n", aux);
	if (verify_rep_value(w_env, aux))
	{
		printf("Hay una variable repetida\n");
		return (1);
	}
	free(aux);
	return (0);
}

void	delete_env_var(t_env **env, const char *str)
{
	t_env	*prev;
	t_env	*current;
	char	*aux;

	prev = NULL;
	current = *env;
	aux = rm_value(str, '=');
	while (current != NULL)
	{
		if (!strcmp(current->key, aux))
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_process *pcs, t_all *all)
{
	int	i;

	i = 0;
	if (!pcs->args[1])
		return (0);
	while (pcs->args[++i])
		delete_env_var(&all->w_env, pcs->args[i]);
	return (1);
}

int	ft_export(t_process *pcs, t_all *all)
{
	int	i;

	i = 0;
	if (!pcs->args[1]) // if there is just 1 arg
		show_exp(all->w_env); // just show it
	else
	{
		while(pcs->args[++i])
		{
			delete_env_var(&all->w_env, pcs->args[i]);
			save_var_env(pcs->args[i], all);
		}
	}
	return (0);
}
