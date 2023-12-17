/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/17 13:36:00 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	check_heredoc(t_all *all)
{
	t_token		*current_rd;

	current_rd = all->prcs->rd;
	while (current_rd != NULL)
	{
		if (current_rd->type == RDHD)
			create_heredoc(all);
		current_rd = current_rd->next;
	}
}

void	create_heredoc(t_all *all)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	int		err;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		save_hd_fd(all, all->prcs, fd);
	if (ft_close(&fd[1]) == -1)
		exit(kill(pid, SIGTERM));
	if (waitpid(pid, &status, 0) == -1)
		ft_close(&fd[0]);
	if (WIFEXITED(status))
	{
		err = WEXITSTATUS(status);
		if (err == 1)
			g_sig = 1;
		else if (err == 2)
			ft_error(all, err, NULL);
	}
	// dprintf(0, "fd[1]: %i\n", fd[1]);
	// close(fd[1]);
	all->prcs->rd->fd_read_hd = fd[0];
}

void	save_hd_fd(t_all *all, t_process *prcs, int fd[2])
{
	char	*line;

	line = NULL;
	(void)all;
	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || prcs == NULL || prcs->rd == NULL \
			|| prcs->rd->wrd == NULL)
			break ;
		if (ft_strcmp(line, prcs->rd->wrd) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		do_sigign(SIGQUIT);
	}
	if (ft_close(&fd[1]) == -1 || ft_close(&fd[0]) == -1)
		exit(2);
	exit(0);
}

int	ft_close(int *fd)
{
	if (*fd > 0 && close(*fd) == -1)
	{
		*fd = 0;
		return (-1);
	}
	*fd = 0;
	return (0);
}
