/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 18:37:51 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	redi_type(t_all *all, t_process *prcs, int fd_pipe[2])
{
	if (prcs->rd->type == RDIN)
		open_infile(all->prcs, fd_pipe);
	else if (prcs->rd->type == RDOUT)
		open_outfile(all->prcs, fd_pipe);
	else if (prcs->rd->type == RDHD)
		here_doc(all->prcs, fd_pipe);
	else if (prcs->rd->type == RDAP)
		apendd(all->prcs, fd_pipe);
	else
		printf("hi ha redi pero ninguna del type que volem, so s'ha de mirar\n");
}

void	open_infile(t_process *prcs, int fd_pipe[2])
{
	prcs->rd->open = open(prcs->rd->wrd, O_RDONLY);
	dup2(prcs->rd->open, STDIN_FILENO);
	close_pipes(fd_pipe);
	close(prcs->rd->open);
}

void	open_outfile(t_process *prcs, int fd_pipe[2])
{
	prcs->rd->open = open(prcs->rd->wrd, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	dup2(prcs->rd->open, STDOUT_FILENO);
	close_pipes(fd_pipe);
	close(prcs->rd->open);
}

void	apendd(t_process *prcs, int fd_pipe[2])
{
	prcs->rd->open = open(prcs->rd->wrd, O_WRONLY | O_APPEND | O_CREAT, 0666);
	dup2(prcs->rd->open, STDOUT_FILENO);
	close_pipes(fd_pipe);
	close(prcs->rd->open);
}

void	here_doc(t_process *prcs, int fd_pipe[2])
{
	dup2(prcs->fd_read_hd, STDIN_FILENO);
	close(prcs->fd_read_hd);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
}
