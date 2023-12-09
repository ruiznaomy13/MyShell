/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/09 15:19:19 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all		all;

	(void)ac;
	printf("av:%s\n", av[0]);
	signals();
	ft_bzero(&all, sizeof(t_all));
	all.env = duplicate_env(env);
	list_env(&all, env);
	loop(&all);
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
	if (!aux){
		printf("no hi ha redi(mostra redi)\n");
		return ;
	}
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
		if (aux->rd)
			mostra_rd(aux);
		j++;
		aux = aux->next;
	}
}


void	ft_free_all(t_all *all)
{
	t_token		*tkn;
	t_token		*rd;
	t_process	*prc;

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

	printf("Free hecho.\n");
}

// void	free_prcs(t_all *all)
// {
// 	t_process	*prc;
// 	t_token		*rd;
// 	int			i;
	
// 	i = 0;
// 	prc = all->prcs;
// 	while (all->prcs != NULL)
// 	{
// 		while (prc->rd)
// 		{
// 			rd = prc->rd;
// 			prc->rd = prc->rd->next;
// 			free(rd->wrd);
// 			free(rd);
// 		}
// 		all->prcs = all->prcs->next;
// 		while (prc->args[++i])
// 			free(prc->args[i]);
// 		free(prc->args);
// 		free(prc);
// 	}
// }

// void	free_token(t_token *tkn)
// {
// 	t_token	*current;
// 	t_token	*temp;

// 	current = tkn;
//     while (current != NULL)
// 	{
//         temp = current;
//         current = current->next;
//         free(temp->wrd);
//         free(temp);
//     }
// }

// void	ft_free(t_all *all)
// {
// 	t_token		*tkn;
// 	int			i;

// 	i = -1;
// 	while (all->token != NULL)
// 	{
// 		tkn = all->token;
// 		all->token = all->token->next;
// 		free(tkn->wrd);
// 		free(tkn);
// 	}
// 	free_prcs(all);
// 	all->token = NULL;
// 	all->prcs = NULL;
// }