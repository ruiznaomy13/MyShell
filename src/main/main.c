/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/30 16:31:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all		all;

	(void)ac;
	(void)av;
	all.env = env;
	ft_bzero(&all, sizeof(t_all));
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

void    mostra_rd(t_process *pcs)
{
        int                     i;
        t_token         *aux;

        i = 1;
        aux = pcs->rd;
        while (aux != NULL)
        {
			printf("REDIRECCIONES =\n");
            printf("%d = %s -> %d\n", i, aux->wrd, aux->type);
            i++;
            if (i == 10)
            	return ;
			aux = aux->next;
        }
}

void	mostra_process(t_all *all)
{
	int			i;
	t_process	*aux;

	aux = all->process;
	printf("ARGUMENTS =");
	while (aux != NULL)
	{
		i = -1;
		while (aux->args[++i] != NULL)
		{
			printf("arg:<%s>", aux->args[i]);
		}
		aux = aux->next;
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
	while (all->process != NULL)
	{
		prc = all->process;
		all->process = all->process->next;
		free(prc);
	}
}
