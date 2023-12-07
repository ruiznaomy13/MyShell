/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 13:59:48 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/04 20:41:01 by ncastell         ###   ########.fr       */
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