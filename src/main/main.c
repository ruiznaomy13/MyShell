/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/29 19:37:24 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sun_header(void)
{
	printf(YELLOW"\n");
	printf("			           ¶\n");
	printf("			     ¶      ¶      ¶\n");
	printf("			      ¶¶   ¶¶¶   ¶¶\n");
	printf("			      ¶¶¶       ¶¶¶\n");
	printf("			 ¶     ¶  ¶¶¶¶¶  ¶     ¶\n");
	printf("			 ¶¶¶¶¶  ¶¶¶¶¶¶¶¶¶  ¶¶¶¶¶\n");
	printf("			   ¶¶  ¶¶¶¶¶¶¶¶¶¶¶  ¶¶\n");
	printf("			      ¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("			¶¶¶¶ ¶¶¶¶¶¶¶¶¶¶¶¶¶¶  ¶¶¶¶\n");
	printf("			      ¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("			   ¶¶  ¶¶¶¶¶¶¶¶¶¶¶  ¶¶\n");
	printf("			  ¶¶¶   ¶¶¶¶¶¶¶¶¶  ¶¶¶¶\n");
	printf("			 ¶        ¶¶¶¶¶        ¶\n");
	printf("			      ¶¶¶       ¶¶¶\n");
	printf("	 		     ¶¶   ¶¶¶   ¶¶\n");
	printf("			     ¶¶     ¶     ¶¶\n");
	printf("			            ¶\n\n"WHITE);
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
