/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:09:45 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/23 12:50:25 by ncastell         ###   ########.fr       */
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

void	free_rd(t_process *prc)
{
	t_token	*aux_rd;

	while (prc != NULL && prc->rd != NULL)
	{
		aux_rd = prc->rd;
		prc->rd = prc->rd->next;
		free(aux_rd);
	}
	prc->rd = NULL;
}

void	free_process(t_process *prcs)
{
	t_process	*temp;

	while (prcs != NULL)
	{
		temp = prcs;
		prcs = prcs->next;
		free_token_list(temp->rd);
		free_char_array(&temp->args);
		free(temp->ruta);
		free(temp);
	}
}

void	ft_free_all(t_all *all, int exit)
{
	free(all->line);
	// free_token_list(all->token);
	if (exit)
	{
		clear_history();
		free_char_array(&all->env);
		free_env_list(all->w_env);
	}
	free_process(all->prcs);
	all->prcs = NULL;
	all->token = NULL;
}
