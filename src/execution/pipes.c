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

void wait_pipes(int num_process, pid_t pid)
{
    int 	i;
	int 	status;
	// (void)num_process;
	i = 0;
	// if (all->prcs->pid_prc == wait(&status))
	// 	return ;
/*
	while (num_process > i++)
	{
		int waittest = wait(&status);
		dprintf(2, "wait::::%i\n", all->prcs->pid_prc);
		//dprintf(2, "childwait::::%i\n", waittest);
		if (all->prcs->pid_prc == waittest)
		{
			//dprintf(2 , "aaaaaaaaaaaaaa,\n");
			return ;
			// if (WIFEXITED(status))
			// 	cmd->err = WEXITSTATUS(status);
			// else if (WIFSIGNALED(status))
			// {
			// 	if (WTERMSIG(status) == SIGINT)
			// 		cmd->err = 130;
			// 	else if (WTERMSIG(status) == SIGQUIT)
			// 		(1 && (cmd->err = 131) && (printf("Quit: 3\n")));
			// }
		}
	}*/
	// dprintf(2, "wait::::%i\n", all->prcs->pid_prc);
	while (num_process > i++)
		if (pid == waitpid(-1, &status, 0))
			;
}

