/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:49:42 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/24 18:21:44 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

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

void	free_args_and_rd(t_all *all, t_process *aux_prcs)
{
	int			i;

	all->prcs = aux_prcs;
	while (all && all->prcs && all->prcs->args)
	{
		i = 0;
		while (all->prcs->args && all->prcs->args[i])
		{
			free(all->prcs->args[i]);
			i++;
		}
		free(all->prcs->args);
		all->prcs->args = NULL;
		while (all->prcs->rd)
			free_rd_execve(all);
		free_prcs_execve(all);
	}
}

void	free_rd_execve(t_all *all)
{
	t_token	*aux_rd;

	aux_rd = NULL;
	if (all->prcs->rd)
		aux_rd = all->prcs->rd->next;
	free(all->prcs->rd->wrd);
	free(all->prcs->rd);
	all->prcs->rd = aux_rd;
}

void	free_prcs_execve(t_all *all)
{
	t_process	*next;

	next = NULL;
	if (all->prcs)
	{
		if (all->prcs->next)
			next = all->prcs->next;
		free(all->prcs);
		all->prcs = next;
	}
}
