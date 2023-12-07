/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:15 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/07 18:50:52 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	loop(t_all *all)
{
	while (42)
	{
		all->line = readline("myshell🌞> ");
		if (!all->line)
			return ;
		add_history(all->line);
		if (check_cometes(all, all->line) > 30)
		{
			ft_free(all);
			continue ;
		}
		if (lexer(all))
			continue ;
		if (checker(all))
		{
			ft_free(all);
			continue ;
		}
		ft_putstr_fd("HOLA FD\n", 2);
		// ft_dprintf("Hola %s\n", "Naomy");
		parser(all);
		ft_dprintf("errorrr\n");
		if ((all->num_process == 1) && is_builting(all->prcs->args[0]))
			executor_builting(all, all->prcs);
		else
			executor(all);
		ft_free(all);
	}
}

int	lexer(t_all *all)
{
	int		i;

	i = -1;
	if (all->line == NULL)
		return (1);
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
	return (0);
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
