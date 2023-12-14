/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:54 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/14 21:41:39 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

// char	**duplicate_env(char **env)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	while (env[i++])
// 		;
// 	new_env = (char **)malloc(sizeof(char *) * i + 1);
// 	i = 0;
// 	while (env[i])
// 	{
// 		new_env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	return (new_env);
// }

void	count_process(t_all *all, char *str)
{
	t_token	*aux;

	(void)str;
	aux = all->token;
	all->num_process = 1;
	while (aux)
	{
		if (aux->type == PIPE)
			all->num_process++;
		aux = aux->next;
	}
}
