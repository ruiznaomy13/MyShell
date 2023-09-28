#include "inc/minishell.h"

void	save_redirecions(t_token *tkn, t_process *pcs)
{
	/*if (tkn != NULL && tkn->type != PIPE)
	{
		if (tkn->type == RDOUT || tkn->type == RDAP \
			|| tkn->type == RDIN || tkn->type == RDHD)
            {
                pcs->rd->type = tkn->type;
                tkn = tkn->next
                pcs->rd->wrd = tkn->wrd;
            }
	}*/
	pcs->rd->type = tkn->type;
    tkn = tkn->next;
    pcs->rd->wrd = tkn->wrd;
}

void	*save_args(t_token *tkn, t_process *pcs)
{
	char	**str;
	int		i;

	i = arg_size(tkn);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (tkn != NULL && tkn->type != PIPE)
	{
		if (tkn->type == RDOUT || tkn->type == RDAP \
			|| tkn->type == RDIN || tkn->type == RDHD)
			{
				save_redirecions(tkn, pcs);
				tkn = tkn->next->next;
			}
		if (tkn->wrd != NULL)
		{
			str[i++] = tkn->wrd;
			pcs->pos_args++;
		}
		tkn = tkn->next;
	}
	str[i] = NULL;
	return (str);
}

void	create_process(t_all *all)
{
	//int			i;
	t_process	*pcs;
	t_token		*tkn;

	//i = -1;
	tkn = all->token;
	pcs = (t_process *)ft_calloc(sizeof(t_process), all->num_process);
	if (pcs == NULL)
		return ;
	while (tkn != NULL)
	{
		if (tkn->type == PIPE)
		{
			printf("tkn: %s\n", tkn->wrd);
			pcs = pcs->next;
			tkn = tkn->next;
			printf("tkn->next: %s\n", tkn->wrd);
		}
		/*if (tkn->type == RDOUT || tkn->type == RDAP \
			|| tkn->type == RDIN || tkn->type == RDHD)
		{
			save_redirecions(tkn, pcs);
			tkn = tkn->next->next;
		}*/
		pcs->args = save_args(tkn, pcs);
		while (pcs->pos_args > 0)
		{
			printf("%i\n", pcs->pos_args);
			tkn = tkn->next;
			pcs->pos_args--;
		}
		printf("%i\n", pcs->pos_args);

	}
	all->process = pcs;
}