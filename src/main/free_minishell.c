/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:09:45 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/30 15:16:07 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_token_list(t_token *token)
{
	t_token	*temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->wrd);
		free(temp);
	}
}

void	ft_free_all(t_all *all, int exit)
{
	free(all->line);
	if (exit)
	{
		clear_history();
		free_char_array(&all->env);
		free_env_list(all->w_env);
	}
	all->prcs = NULL;
	all->token = NULL;
}
