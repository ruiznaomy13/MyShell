/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/21 15:58:23 by mmonpeat         ###   ########.fr       */
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
		exit(1);//ft_error(all, -1, NULL); ?
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		save_hd_fd(all, current_rd->wrd, fd);
	if (ft_close(&fd[1]) == -1)
		exit(kill(pid, SIGTERM));
	if (waitpid(pid, &status, 0) == -1)
		close(fd[0]);
		// ft_close(&fd[0]);
	if (WIFEXITED(status))
	{
		err = WEXITSTATUS(status);
		if (err == 1)
			g_sig = 1;
		else if (err == 2)
			ft_error(all, err, NULL);
	}
	current_rd->fd_read_hd = fd[0];
	printf("1.fd[0]: %i\n", current_rd->fd_read_hd);
}

void	save_hd_fd(t_all *all, char *wrd, int fd[2])
{
	char	*line;

	(void)all;
	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	// int aa = fd[1];
	line = readline(">> ");
	// printf("delimitadors: %s   line: %s fd[1]: %i aa: %i\n", wrd, line, fd[1], aa);
	while (line && ft_strncmp(line, wrd, ft_strlen(line)))//ft_strlen(wrd)
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		// dup2(fd[1], aa);
		// if (write(fd[1], line, ft_strlen(line)) == -1 \
		// 	|| write(fd[1], "\n", 1) == -1)
		// {
		// 	ft_free_hd(&line, 2);
		// 	ft_close(&fd[0]);
		// 	ft_close(&fd[1]);
		// 	exit(2);
		// }
		// ft_free_hd(&line, 2);
		free(line);
		do_sigign(SIGQUIT);
		line = readline("> ");
	}
	// ft_free_hd(&line, 2);
	free(line);
	// if (ft_close(&fd[1]) == -1 || ft_close(&fd[0]) == -1)
	// 	exit(2);
	close(fd[1]);
	// close(fd[0]);
	exit(0);
}

int	ft_close(int *fd)
{
	printf("entra a ft_colose fd: %i\n", *fd);
	if (*fd > 0 && close(*fd) == -1)
	{
		*fd = 0;
		return (-1);
	}
	*fd = 0;
	return (0);
}

void	*ft_free_hd(char **matrix, int option)
{
	int	i;

	if (matrix && option == 1)
	{
		i = 0;
		while (matrix[i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
	}
	else if (matrix && *matrix && option == 2)
	{
		free(*matrix);
		*matrix = NULL;
	}
	matrix = NULL;
	return (NULL);
}
/*
int fd_aux = dup(all->prcs->rd->fd_read_hd);
	char buff[100]
	read(fd_aux, buff, 100);
	write(1, buff, 100);
*/