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
    while (num_process > i++)
        waitpid(-1, &status, 0);//wait(&status);
}

void check_pipes(int input_pipe[2], int output_pipe[2])
{
	//printf("\n\n\nCHECK_PIPES:\ninput_pipe[0]: %i\ninput_pipe[1]: %i\noutput_pipe[0]: %i\noutput_pipe[1]: %i\n", input_pipe[0], input_pipe[1], output_pipe[0], output_pipe[1]);
    if (input_pipe[0] != -1)
	{
		//printf("\ninput_pipe[0] != -1:\ninput_pipe[0]: %i\ninput_pipe[1]: %i\noutput_pipe[0]: %i\noutput_pipe[1]: %i\n", input_pipe[0], input_pipe[1], output_pipe[0], output_pipe[1]);
		close(0);
		dup2(input_pipe[0], STDIN_FILENO);
		close(input_pipe[0]);
		//close(input_pipe[1]);//no cal es tanca despres
		//printf("\nCOLOSED:input_pipe[0] != -1:\ninput_pipe[0]: %i\ninput_pipe[1]: %i\noutput_pipe[0]: %i\noutput_pipe[1]: %i\n", input_pipe[0], input_pipe[1], output_pipe[0], output_pipe[1]);
	}
	if (output_pipe[1] != -1)
	{
		//printf("\noutput_pipe[1] != -1:\ninput_pipe[0]: %i\ninput_pipe[1]: %i\noutput_pipe[0]: %i\noutput_pipe[1]: %i\n", input_pipe[0], input_pipe[1], output_pipe[0], output_pipe[1]);
		//close(1);
		dup2(output_pipe[1], STDOUT_FILENO);
		//close(output_pipe[0]);//no cal es tanca despres
		close(output_pipe[1]);
		//printf("\nCLOSED: output_pipe[1] != -1:\ninput_pipe[0]: %i\ninput_pipe[1]: %i\noutput_pipe[0]: %i\noutput_pipe[1]: %i\n", input_pipe[0], input_pipe[1], output_pipe[0], output_pipe[1]);
	}
}