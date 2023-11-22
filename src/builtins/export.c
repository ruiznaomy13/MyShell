/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/22 19:39:19 by ncastell         ###   ########.fr       */
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
	if(dup_src[1])
	{
		aux_env->equal = 1;
		aux_env->value = ft_strdup(dup_src[1]);
	}
	else
		aux_env->value = NULL;
	add_to_env(all, aux_env);
	free_char_array(dup_src);
	printf("llego aqui\n");
	return (0);
}

int	ft_export(t_process *pcs, t_all *all)
{
	int	i;

	i = -1;
	if (!pcs->args[1]) // if there is just 1 arg
		show_exp(all->w_env); // just show it
	// else
	// {
	// 	while(pcs->args[++i])
	// 	{
			// if (check_var(pcs->args[i], all->env)) // if it exist
			// 	delete_var(all->env); // we delete it
			save_var_env(pcs->args[1], all); // and save the new arg
	// 	}
	// }
	return (0);
}