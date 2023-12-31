/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:15 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/31 14:41:44 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_all *all)
{
	while (42)
	{
		init_signals(NORM);
		do_sigign(SIGQUIT);
		all->line = readline(CYAN"myShell🌞> "WHITE);
		do_sigign(SIGINT);
		if (!all->line)
			exit_prog(all, 0);
		else if (*all->line)
			add_history(all->line);
		if (minishell_structure(all))
			continue ;
		if (g_sig)
			all->error = g_sig;
		if (exec_parent(all))
			executor_builting(all, all->prcs);
		else
			executor(all);
		g_sig = 0;
		ft_free_all(all, SUCCESS);
	}
}

int	minishell_structure(t_all *all)
{
	if (check_cometes(all, all->line) > 30)
	{
		ft_free_all(all, 0);
		return (1);
	}
	if (lexer(all))
		return (1);
	if (checker(all))
	{
		ft_free_all(all, 0);
		return (1);
	}
	if (parser(all))
	{
		all->error = g_sig;
		g_sig = 0;
		free_args_and_rd(all, all->prcs);
		ft_free_all(all, 0);
		return (1);
	}
	return (0);
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
		tkn->wrd = ft_strdup("|");
	else if (type == RDAP)
		tkn->wrd = ft_strdup(">>");
	else if (type == RDHD)
		tkn->wrd = ft_strdup("<<");
	else if (type == RDOUT)
		tkn->wrd = ft_strdup(">");
	else if (type == RDIN)
		tkn->wrd = ft_strdup("<");
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
