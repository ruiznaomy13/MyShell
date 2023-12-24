/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:49:42 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/24 18:10:17 by mmonpeat         ###   ########.fr       */
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
		{
			t_token *aux_rd = NULL;
			if (all->prcs->rd)
				aux_rd = all->prcs->rd->next;
			free(all->prcs->rd->wrd);
			free(all->prcs->rd);
			all->prcs->rd = aux_rd;
		}
		if (all->prcs)
		{
			t_process *next = NULL;
			if (all->prcs->next)
				next = all->prcs->next;
			free(all->prcs);
			all->prcs = next;
		}
	}
}
/*
//sense segfoult
void	free_args_and_rd(t_all *all, t_process *aux_prcs)
{
	int			i;
	t_token		*next_rd;
	t_process	*next_prcs;

	all->prcs = aux_prcs;
	while (all && all->prcs)
	{
		i = 0;
		ft_dprintf("\n\n\nFREEE prcs:%p\n", all->prcs);
		while (all->prcs->args && all->prcs->args[i])
			free(all->prcs->args[i++]);
		free(all->prcs->args);
		while (all->prcs->rd && all->prcs->rd->wrd)
		{
			free(all->prcs->rd->wrd);
			next_rd = all->prcs->rd->next;
			free(all->prcs->rd);
			all->prcs->rd = next_rd;
		}
		next_prcs = all->prcs->next;
		free(all->prcs);
		all->prcs = next_prcs;
	}
}
*/