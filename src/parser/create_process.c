/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 14:10:01 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	rm_prev_tkns(t_all *all)
{
	t_token	*aux;

	while (all->token != NULL)
	{
		aux = all->token;
		all->token = all->token->next;
		if (aux->type == PIPE)
		{
			free(aux);
			return ;
		}
		free(aux);
	}
}

void	add_prcs(t_all *all, t_process *pcs)
{
	t_process	*aux;

	if (all->prcs == NULL)
		all->prcs = pcs;
	else
	{
		aux = all->prcs;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = pcs;
	}
}

void	create_process(t_all *all)
{
	t_process	*pcs;

	while (all->token != NULL)
	{
		pcs = (t_process *)ft_calloc(sizeof(t_process), 1);
		if (pcs == NULL)
			return ;
		pcs->args = save_arg(all);
		list_redirection(pcs, all);
		rm_prev_tkns(all);
		add_prcs(all, pcs);
	}
	mostra_process(all);
}

int	check_heredoc(t_all *all)
{
	t_process	*prcs;
	int			i;

	prcs = all->prcs;
	i = 1;
	while (prcs != NULL)
	{
		if (prcs->rd)
		{
			while (prcs->rd != NULL)
			{
				if (prcs->rd->type == RDHD)
					return (i);
				prcs->rd = prcs->rd->next;
			}
		}
		i++;
		prcs = prcs->next;
	}
	return (0);
}

void	parser(t_all *all)
{
	int	i;

	i = 0;
	count_process(all, all->line);
	printf("num processs %i\n", all->num_process);
	create_process(all);
	if (check_heredoc(all) != 0)
	{
		i = check_heredoc(all);
		save_hd_fd(all->prcs, i);
	}
}
