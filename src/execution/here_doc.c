/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/03 16:15:24 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	save_hd_fd(t_process *prcs)
{
	char	*line;
	int		fd[2];

	line = NULL;
	if (pipe(fd) == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, prcs->rd->wrd) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	prcs->fd_read_hd = fd[0];
	close(fd[1]);
}
