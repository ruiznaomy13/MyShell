/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/16 13:01:39 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	save_hd_fd(t_process *prcs, int i)
{
	char	*line;
	int		fd[2];
	int		poss;

	line = NULL;
	poss = 0;
	if (pipe(fd) == -1)
		exit(1);//ft_error();
	while (++poss < i)
		prcs = prcs->next;
	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	// if (g_sig == 1)
	// 	exit (0);
	while (1)
	{
		printf("22222 var gloval : %i\n", g_sig);
		if (g_sig == 1)
			break ;
		line = readline("> ");
		if (line == NULL)
			break ;
		if (prcs == NULL || prcs->rd == NULL || prcs->rd->wrd == NULL)
			break ;
		if (ft_strcmp(line, prcs->rd->wrd) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		do_sigign(SIGQUIT);
	}
	prcs->fd_read_hd = fd[0];
	close(fd[1]);
}
