/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/30 13:20:10 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	 check_exp_var(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '='))
		i++;
	if (i < ft_strlen(str))
	{
		printf("ENTRO = %s\ni = %zu && len = %zu\n", str, i, ft_strlen(str));
		return (1);
	}
	return (0);
}

void	show_sorted_exp(t_env *env)
{
	order_exp(env);
	while (env != NULL)
	{
		printf("declare -x %s", env->key);
		if (env->equal && !env->value)
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
		while (pcs->args[++i])
		{
			delete_env_var(&all->w_env, pcs->args[i]);
			if (check_exp_var(pcs->args[i]))
				all->error = print_error(pcs->args[1], 2, 1);
			else
				save_var_env(pcs->args[i], all);
		}
	}
	return (0);
}
