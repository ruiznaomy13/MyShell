/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/11/15 19:56:47 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_sig_ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

void	signals(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_ctr_c);
	
}

int	main(int ac, char **av, char **env)
{
	signals();
	
	t_all		all;

	(void)ac;
	(void)av;
	//signals();
	ft_bzero(&all, sizeof(t_all));
	all.env = duplicate_env(env);
	loop(&all);
	ft_free(&all);
	return (0);
}

void	mostra_tokens(t_all *all)
{
	int			i;
	t_token		*aux;

	i = 1;
	aux = all->token;
	while (aux != NULL)
	{
		printf("%d = %s -> %d\n", i, aux->wrd, aux->type);
		aux = aux->next;
		i++;
	}
}

void	mostra_rd(t_process *pcs)
{
	int			i;
	t_token		*aux;

	i = 1;
	aux = pcs->rd;
	printf("REDIRECCIONES =\n");
	while (aux != NULL)
	{
		printf("%d = %s -> %d\n", i, aux->wrd, aux->type);
		aux = aux->next;
		i++;
		if (i == 10)
			return ;
	}
}

void	mostra_process(t_all *all)
{
	int			i;
	int			j;
	t_process	*aux;

	j = 1;
	aux = all->prcs;
	while (aux != NULL)
	{
		i = -1;
		printf("\n\nPROCESS %d =\n", j);
		while (aux->args && aux->args[++i] != NULL)
			printf("[%s] ", aux->args[i]);
		printf("\n");
		mostra_rd(aux);
		j++;
		aux = aux->next;
	}
}

void	ft_free(t_all *all)
{
	t_token		*tkn;
	t_process	*prc;

	while (all->token != NULL)
	{
		tkn = all->token;
		all->token = all->token->next;
		free(tkn);
	}
	while (all->prcs != NULL)
	{
		prc = all->prcs;
		all->prcs = all->prcs->next;
		free(prc);
	}
}
