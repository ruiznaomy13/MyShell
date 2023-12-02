/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/02 18:29:06 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	save_hd_fd(t_process *prcs)
{
	char	*line;
	int		fd[2];

	line = NULL;
    printf("save write pipe\n");
	if (pipe(fd) == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, prcs->rd->wrd) == 0)
			break ;
		dup2(fd[0], STDIN_FILENO);
	}
	close(fd[0]);
	int fd_read_hd = fd[1];
	printf("fd_read_hd %i\n", fd_read_hd);
	close(fd[1]);
}
