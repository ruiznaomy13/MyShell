/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/21 17:49:31 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	check_heredoc(t_all *all, t_process *prcs)
{
	t_token		*current_rd;

	current_rd = prcs->rd;
	while (current_rd != NULL)
	{
		if (current_rd->type == RDHD)
			create_heredoc(all, current_rd);
		current_rd = current_rd->next;
	}
}

void	create_heredoc(t_all *all, t_token *current_rd)
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
		save_hd_fd(all, current_rd->wrd, fd);
	if (ft_close(&fd[1]) == -1)
		exit(kill(pid, SIGTERM));
	if (waitpid(pid, &status, 0) == -1)
		close(fd[0]);
	if (WIFEXITED(status))
	{
		err = WEXITSTATUS(status);
		if (err == 1)
			g_sig = 1;
		else if (err == 2)
			ft_error(all, err, NULL);
	}
	current_rd->fd_read_hd = fd[0];
}

void	save_hd_fd(t_all *all, char *wrd, int fd[2])
{
	char	*line;

	(void)all;
	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	line = readline("> ");
	while (line && ft_strncmp(line, wrd, ft_strlen(line)))
	{
		if (write(fd[1], line, ft_strlen(line)) == -1 \
			|| write(fd[1], "\n", 1) == -1)
		{
			free(line);
			ft_close(&fd[0]);
			ft_close(&fd[1]);
			exit(2);
		}
		free(line);
		do_sigign(SIGQUIT);
		line = readline("> ");
	}
	free(line);
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
