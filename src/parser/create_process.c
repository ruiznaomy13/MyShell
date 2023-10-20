/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/03 12:06:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void rm_prev_tkns(t_all *all)
{
	t_token *aux;
	
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

void add_prcs(t_all *all, t_process *pcs)
{
    t_process *aux;

    if (all->prcs == NULL) {
        all->prcs = pcs;
	} else
    {
        aux = all->prcs;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = pcs;
    }
}

void create_process(t_all *all)
{
    t_process *pcs;

    while (all->token != NULL)
    {
        pcs = (t_process *)ft_calloc(sizeof(t_process), 1);
        if (pcs == NULL)
            return ;
        pcs->args = save_arg(all);
        list_redirection(pcs, all);
		printf("NEW FIRST TOKEN = %s\n", all->token->wrd);
        rm_prev_tkns(all);
        add_prcs(all, pcs);
    }
	mostra_process(all);
}

void	parser(t_all *all)
{
    count_process(all, all->line);
    create_process(all);
}