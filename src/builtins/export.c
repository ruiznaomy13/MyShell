/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 14:12:47 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	show_sorted_exp(t_env *env)
{
	order_exp(env);
	while (env != NULL)
	{
		printf("declare -x %s", env->key);
		if (env->equal)
			printf("=");
		if (env->value)
			printf("%s", env->value);
		printf("\n");
		env = env->next;
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
	if (!pcs->args[1])
		show_sorted_exp(all->w_env);
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
