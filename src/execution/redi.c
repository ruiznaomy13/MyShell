#include "inc/minishell.h"

void redi_type(t_all *all, t_process *prcs, int input_pipe[2], int output_pipe[2])
{
    if (prcs->rd->type == RDIN)
		open_infile(all->prcs, input_pipe, output_pipe);
	else if (prcs->rd->type == RDOUT)
		open_outfile(all->prcs, input_pipe, output_pipe);
	else if (prcs->rd->type == RDHD)
		here_doc(all->prcs, input_pipe, output_pipe);
	else if (prcs->rd->type == RDAP)
		apendd(all->prcs, input_pipe, output_pipe);
	else
		printf("hi ha redi pero ninguna del type que volem, so s'ha de mirar\n");
}

void	open_infile(t_process *prcs, int input_pipe[2], int output_pipe[2])
{
    printf("i'm in open infile\n");
    if (access(prcs->rd->wrd, F_OK) == -1)
	{
		close_pipes(input_pipe);
        printf("ERROR, redi infile\n");
        exit(1);//exit(ft_error(1, ERR_NFD, prcs->rd->wrd));
	}
	prcs->rd->open = open(prcs->rd->wrd, O_RDONLY);
	if (access(prcs->rd->wrd, R_OK) == -1)
	{
		close_pipes(output_pipe);
        printf("ERROR, redi infile\n");
        exit(1);
		//exit(ft_error(1, ERR_PERM, prcs->rd->wrd));
	}
	dup2(prcs->rd->open, STDIN_FILENO);
	close_pipes(output_pipe);
	close(prcs->rd->open);
}

void	open_outfile(t_process *prcs, int input_pipe[2], int output_pipe[2])
{
	printf("i'm in open outfile\n");
	prcs->rd->open = open(prcs->rd->wrd, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (prcs->rd->open == -1)
	{
		close_pipes(input_pipe);
        printf("ERROR, redi outfile\n");
        exit(1);
		//exit(ft_error(1, ERR_NFD, outfile));
	}
	if (access(prcs->rd->wrd, W_OK) == -1)
	{
		close_pipes(output_pipe);
        printf("ERROR, redi outfile\n");
        exit(1);
		//exit(ft_error(1, ERR_PERM, outfile));
	}
	dup2(prcs->rd->open, STDOUT_FILENO);
    close_pipes(input_pipe);
	close(prcs->rd->open);
}

void here_doc(t_process *prcs, int input_pipe[2], int output_pipe[2])
{
	(void)input_pipe;
	(void)output_pipe;
    (void)prcs;
    printf("redi de here doc\n");
}

void apendd(t_process *prcs, int input_pipe[2], int output_pipe[2])
{
	(void)input_pipe;
	(void)output_pipe;
    (void)prcs;
    printf("redi de apendd\n");
}