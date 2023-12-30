/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/30 17:53:19 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	redi_type(t_all *all, t_process *prcs, int fd_pipe[2])
{
	if (prcs->rd->type == RDIN)
		open_infile(all, all->prcs, fd_pipe);
	else if (prcs->rd->type == RDOUT)
		open_outfile(all, all->prcs, fd_pipe);
	else if (prcs->rd->type == RDHD)
		here_doc(all->prcs, fd_pipe);
	else if (prcs->rd->type == RDAP)
		apendd(all, all->prcs, fd_pipe);
}

void	open_infile(t_all *all, t_process *prcs, int fd_pipe[2])
{
	prcs->rd->open = open(prcs->rd->wrd, O_RDONLY);
	if (prcs->rd->open == -1)
	{
		ft_error(all, ACCESS_ERROR, "no such file or directory");
		exit(1);
	}
	dup2(prcs->rd->open, STDIN_FILENO);
	close_pipes(fd_pipe);
	close(prcs->rd->open);
}

void	open_outfile(t_all *all, t_process *prcs, int fd_pipe[2])
{
	prcs->rd->open = open(prcs->rd->wrd, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (prcs->rd->open == -1)
	{
		ft_error(all, ACCESS_ERROR, "no such file or directory");
		exit(1);
	}
	dup2(prcs->rd->open, STDOUT_FILENO);
	close_pipes(fd_pipe);
	close(prcs->rd->open);
}

void	apendd(t_all *all, t_process *prcs, int fd_pipe[2])
{
	prcs->rd->open = open(prcs->rd->wrd, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (prcs->rd->open == -1)
	{
		ft_error(all, ACCESS_ERROR, "no such file or directory");
		exit(1);
	}
	dup2(prcs->rd->open, STDOUT_FILENO);
	close_pipes(fd_pipe);
	close(prcs->rd->open);
}

void	here_doc(t_process *prcs, int fd_pipe[2])
{
	dup2(prcs->rd->fd_read_hd, STDIN_FILENO);
	close(prcs->rd->fd_read_hd);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
}
