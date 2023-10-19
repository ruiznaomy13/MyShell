/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:15 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/01 00:59:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	loop(t_all *all)
{
	while (1)
	{
		//all->line es null al tornar a entrar al loop
		while(all->line == NULL){
			all->line = readline("myshell🌞> ");
		}
		printf("\nhola line: %s\n", all->line);
		add_history(all->line);
		printf("%s\n", all->line);
		//ft_bzero(&all->token, sizeof(t_token));//no cal crec
		//ft_bzero(&all->prcs, sizeof(t_process));
		checker(all);
		executor(all);
		printf("2222222222222222\n");
		ft_free(all);
		printf("33333333333\n");

		ft_bzero(all->line, sizeof(char));
		//exit(0);
	}
}

int	checker(t_all *all)
{
    if (ft_strlen(all->line) < 1)
        return (0);
    else if (!syntax_checker(all))
    {
        ft_error(5);
        return (0);
    }
    return (1);
}

	coma = check_cometes(all->line);
	if (coma == 34 || coma == 39)
	{
		ft_error(coma);
		exit (1);
	}
	else
	{
		count_process(all, all->line);
		lexer(all);
		mostra_tokens(all);
		create_process(all);
	}
}

void	lexer(t_all *all)
{
	int		i;

	i = -1;
	while (all->line[++i])
	{
		if (!delimiter(all->line[i]))
			i += create_token(all, &all->line[i], TEXT) - 1;
		else if (all->line[i] == '|')
			i += create_token(all, &all->line[i], PIPE) - 1;
		else if (all->line[i] == '>' && all->line[i + 1] == '>')
			i += create_token(all, &all->line[i], RDAP) - 1;
		else if (all->line[i] == '<' && all->line[i + 1] == '<')
			i += create_token(all, &all->line[i], RDHD) - 1;
		else if (all->line[i] == '>')
			i += create_token(all, &all->line[i], RDOUT) - 1;
		else if (all->line[i] == '<')
			i += create_token(all, &all->line[i], RDIN) - 1;
	}
}

int	create_token(t_all *all, char *str, int type)
{
	t_token	*tkn;

	tkn = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!tkn)
		return (0);
	if (type == TEXT || type == EXP)
		tkn->wrd = is_text_first(str);
	else if (type == PIPE)
		tkn->wrd = "|";
	else if (type == RDAP)
		tkn->wrd = ">>";
	else if (type == RDHD)
		tkn->wrd = "<<";
	else if (type == RDOUT)
		tkn->wrd = ">";
	else if (type == RDIN)
		tkn->wrd = "<";
	tkn->type = type;
	add_token(tkn, all);
	return (ft_strlen(tkn->wrd));
}

void	add_token(t_token *tkn, t_all *all)
{
	t_token	*aux;

	if (all->token == NULL)
		all->token = tkn;
	else
	{
		aux = all->token;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = tkn;
	}
}
