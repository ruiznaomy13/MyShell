#include "inc/minishell.h"

void	init_pipes(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

void    close_pipes(int *pipe)
{
	if (pipe[0] != -1)
        close(pipe[0]);
    if (pipe[1] != -1)
        close(pipe[1]);
}

void wait_pipes(int num_process)
{
    int 	i;
	int 	status;

	i = 0;
    while (i++ < num_process)
        wait(&status);
}

void check_pipes(int input_pipe[2], int output_pipe[2])
{
    if (input_pipe[0] != -1)
	{
		close(0);
		dup2(input_pipe[0], STDIN_FILENO);
		close(input_pipe[0]);
	}
	if (output_pipe[1] != -1)
	{
		close(1);
		dup2(output_pipe[1], STDOUT_FILENO);
		close(output_pipe[1]);
	}
}