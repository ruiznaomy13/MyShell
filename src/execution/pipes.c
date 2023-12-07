/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:41 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 18:37:43 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	dup_apunta_terminal(int fd_trm[2])
{
	fd_trm[0] = dup(0);
	fd_trm[1] = dup(1);
}

void	init_pipes(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

void	close_pipes(int *pipe)
{
	if (pipe[0] != -1)
		close(pipe[0]);
	if (pipe[1] != -1)
		close(pipe[1]);
}

void	father_redirect_stdin(int fd_pipe[2])
{
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
}

void	dup2_apunta_terminal(int fd_trm[2])
{
	dup2(fd_trm[0], STDIN_FILENO);
	dup2(fd_trm[1], STDOUT_FILENO);
	close_pipes(fd_trm);
}
