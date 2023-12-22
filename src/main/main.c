/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/22 16:23:37 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all		all;

	(void)ac;
	(void)av;
	g_sig = 0;
	ft_bzero(&all, sizeof(t_all));
	list_env(&all, env);
	loop(&all);
	return (0);
}

void	ft_free_all(t_all *all)
{
	t_token		*tkn;
	t_token		*rd;
	t_process	*prc;
	// t_env		*env;

	while (all->prcs != NULL && all->prcs->rd != NULL)
	{
		rd = all->prcs->rd;
		all->prcs->rd = all->prcs->rd->next;
		free(rd);
	}
	while (all->prcs != NULL)
	{
		prc = all->prcs;
		all->prcs = all->prcs->next;
		free(prc);
	}
	while (all->token != NULL)
	{
		tkn = all->token;
		all->token = all->token->next;
		free(tkn);
	}
}

