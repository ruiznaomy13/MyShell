/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/22 16:41:59 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sun_header(void)
{
	printf(YELLOW"\n");
	printf("				           ¶\n");
	printf("				     ¶      ¶      ¶\n");
	printf("				      ¶¶   ¶¶¶   ¶¶\n");
	printf("				      ¶¶¶       ¶¶¶\n");
	printf("				 ¶     ¶  ¶¶¶¶¶  ¶     ¶\n");
	printf("				 ¶¶¶¶¶  ¶¶¶¶¶¶¶¶¶  ¶¶¶¶¶\n");
	printf("				   ¶¶  ¶¶¶¶¶¶¶¶¶¶¶  ¶¶\n");
	printf("				      ¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("				¶¶¶¶ ¶¶¶¶¶¶¶¶¶¶¶¶¶¶  ¶¶¶¶\n");
	printf("				      ¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("				   ¶¶  ¶¶¶¶¶¶¶¶¶¶¶  ¶¶\n");
	printf("				  ¶¶¶   ¶¶¶¶¶¶¶¶¶  ¶¶¶¶\n");
	printf("				 ¶        ¶¶¶¶¶        ¶\n");
	printf("				      ¶¶¶       ¶¶¶\n");
	printf("	 			     ¶¶   ¶¶¶   ¶¶\n");
	printf("				     ¶¶     ¶     ¶¶\n");
	printf("				            ¶\n\n"WHITE);
}

int	main(int ac, char **av, char **env)
{
	t_all		all;

	(void)ac;
	(void)av;
	g_sig = 0;
	sun_header();
	ft_bzero(&all, sizeof(t_all));
	list_env(&all, env);
	loop(&all);
	return (0);
}

// void	free_env_list(t_env *env)
// {
// 	t_env	*temp;

// 	while (env != NULL)
// 	{
// 		temp = env;
// 		env = env->next;
// 		free(temp->key);
// 		free(temp->value);
// 		free(temp);
// 	}
// }

// void	free_token_list(t_token *token)
// {
// 	t_token	*temp;

// 	while (token != NULL)
// 	{
// 		temp = token;
// 		token = token->next;
// 		free(temp->wrd);
// 		free(temp);
// 	}
// }

// void	free_rd(t_process *prc)
// {
// 	t_token	*aux_rd;

// 	while (prc != NULL && prc->rd != NULL)
// 	{
// 		aux_rd = prc->rd;
// 		prc->rd = prc->rd->next;
// 		free(aux_rd);
// 	}
// 	prc->rd = NULL;
// }

// void	ft_free_all(t_all *all)
// {
// 	t_token		*tkn;
// 	t_process	*prc;

// 	while (all->prcs != NULL)
// 	{
// 		prc = all->prcs;
// 		all->prcs = all->prcs->next;
// 		free_rd(prc);
// 		free(prc);
// 		prc = NULL;
// 	}
// 	all->prcs = NULL;
// 	all->token = NULL;
// }
