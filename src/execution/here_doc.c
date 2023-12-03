/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/03 15:49:29 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	save_hd_fd(t_process *prcs)
{
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	while (1)
	{
		prcs->hd_line = readline("> ");
		if (ft_strcmp(prcs->hd_line, prcs->rd->wrd) == 0)
			break ;
		write(fd[1], prcs->hd_line, ft_strlen(prcs->hd_line));
		write(fd[1], "\n", 1);
	}
	prcs->fd_read_hd = fd[0];
	close(fd[1]);
}
