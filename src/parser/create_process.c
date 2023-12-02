/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/02 17:47:44 by mmonpeat         ###   ########.fr       */
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
		//printf("NEW FIRST TOKEN = %s\n", all->token->wrd);
		rm_prev_tkns(all);
		add_prcs(all, pcs);
	}
	mostra_process(all);
}

int	check_heredoc(t_all *all)
{
	int			i;
	t_token		*aux;

	i = 1;
	aux = all->prcs->rd;
	if (!aux)
	{
		printf("no hi ha redi\n");
		return (0);
	}
	while (aux != NULL)
	{
		if (aux->type == RDHD)
			return (1);
		aux = aux->next;
		// i++;
		// if (i == 10)
		// 	return ;
	}
	return (0);
}

void	parser(t_all *all)
{
	count_process(all, all->line);
	create_process(all);
	if (check_heredoc(all) == 1)//si hi ha un heredoc <<
		save_hd_fd(all->prcs);
}
