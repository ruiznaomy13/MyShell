/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/25 18:03:49 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all		all;

	(void)ac;
	(void)av;
	all.env = env;
	loop(&all);
	// printf("surt");
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

void	mostra_process(t_all *all)
{
	int			i;
	t_process	*aux;

	i = -1;
	aux = all->procesos;
	printf("ARGUMENTS =");
	while (aux->process[++i] != NULL)
	{
		printf("<%s>", aux->process[i]);
	}
	printf("\n");
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
	while (all->procesos != NULL)
	{
		prc = all->procesos;
		all->procesos = all->procesos->next;
		free(prc);
	}
}
