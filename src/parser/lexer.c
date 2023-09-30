/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:15 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/30 15:48:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
void	loop(t_all *all)
{
	while (42)
	{
		all->line = readline("myshell🌞> ");
		add_history(all->line);
		printf("%s\n", all->line);
		checker(all);
		// printf("%s\n", all->env[1]);
		//executor(all);
		ft_free(all);
	}
}

void	checker(t_all *all)
{
	int			coma;

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
		//mostra_process(all);
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
		// if (all->line[i] == '\'')
		// 	i += create_token(all, &all->line[i], COMMA_S) + 1;
		// else if (all->line[i] == '\"')
		// 	i += create_token(all, &all->line[i], COMMA_D) + 1;
		// else if (all->line[i] == '$')
		// 	i += create_token(all, &all->line[i], EXP) - 1;
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
	// Crea el token segun el tipo de dato que ha encontrado
	// if (type == COMMA_S || type == COMMA_D)
	// 	tkn->wrd = is_comma(str, str[0]);
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
	// if (tkn->wrd == NULL)
	// 	return (0);
	tkn->type = type;
	// printf("[ ADDRES ] all -> %p\n", all);
	add_token(tkn, all);
	return (ft_strlen(tkn->wrd));
}

void	add_token(t_token *tkn, t_all *all)
{
	t_token*	aux;

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
