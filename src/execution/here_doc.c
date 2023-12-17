/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:46:40 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/17 16:22:01 by mmonpeat         ###   ########.fr       */
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
			create_heredoc(all, current_rd->wrd);
		current_rd = current_rd->next;
	}
}

void	create_heredoc(t_all *all, char *wrd)
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
		save_hd_fd(all, wrd, fd);
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
	all->prcs->rd->fd_read_hd = fd[0];
}

void	save_hd_fd(t_all *all, char *wrd, int fd[2])
{
	char	*line;

	(void)all;
	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	line = readline("> ");
	printf("delimitadors: %s\n", wrd);
	while (line && ft_strncmp(line, wrd, ft_strlen(wrd)))
	{
		if (write(fd[1], line, ft_strlen(line)) == -1 \
			|| write(fd[1], "\n", 1) == -1)
		{
			ft_free_hd(&line, 2);
			ft_close(&fd[0]);
			ft_close(&fd[1]);
			exit(2);
		}
		ft_free_hd(&line, 2);
		do_sigign(SIGQUIT);
		line = readline("> ");
	}
	ft_free_hd(&line, 2);
	if (ft_close(&fd[1]) == -1 || ft_close(&fd[0]) == -1)
		exit(2);
	exit(0);
}
/* //ABANS DE MIRAR DEL ERIC LA DESPERACIO FA MAL
void save_hd_fd(t_all *all, t_process *prcs, int fd[2])
{
	char *line;

	line = NULL;
	(void)all;
	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || prcs == NULL || prcs->rd == NULL || wrd == NULL)
			break;
		if (ft_strcmp(line, prcs->rd->wrd) == 0)
			break;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		do_sigign(SIGQUIT);
	}
	if (ft_close(&fd[1]) == -1 || ft_close(&fd[0]) == -1)
		exit(2);
	exit(0);
}*/

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
