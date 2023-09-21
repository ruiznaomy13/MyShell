/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:15 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/21 13:31:59 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//nit, no probat
int	check_cometes(char *str)
{
	int		i;
	int		coma;
	int		flag;

	i = 0;
	coma = 0;
	flag = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag == 0)
		{
			coma = str[i];
			flag = 1;
		}
		else if (coma == str[i] && flag == 1)
			flag = 0;
		i++;
	}
	if (flag == 1)
		return (coma);
	else
		return (flag);
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

	if (all->token == NULL)// Si la lista está vacía, el nuevo nodo se convierte en la cabeza de la lista
		all->token = tkn;
	else// Si la lista no está vacía, agregamos el nuevo nodo al final
	{
		aux = all->token;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = tkn;
	}
}

