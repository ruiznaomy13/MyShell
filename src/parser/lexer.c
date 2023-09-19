/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:15 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/19 16:08:06 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	lexer(t_all *all)
{
	int		i;

	i = -1;
	while (all->line[++i])
	{
		// if (all->line[i] == '\'')
		// 	i += create_token(all, &all->line[i], COMMA_S) + 1;
		// else if (all->line[i] == '\"')
		// 	i += create_token(all, &all->line[i], COMMA_D) + 1;
		if (!delimiter(all->line[i]))
			i += create_token(all, &all->line[i], TEXT) - 1;
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
	// Crea el token segun ell tipo de dato que ha encontrado
	if (type == COMMA_S || type == COMMA_D)
		tkn->wrd = is_comma(str, str[0]);
	else if (type == TEXT || type == EXP)
		tkn->wrd = is_text_maria(str);
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
		printf("token: %s\n", aux->wrd);
		aux->next = tkn;
	}
}
/*
void create_proces(t_all *all)
{
	t_proces *current_proces = NULL;
	t_proces *first_proces = NULL;
	t_proces *new_proces;

	while (all->token != NULL)
	{
		if (all->token->type != PIPE)
		{
			// Crear un nuevo proceso para el token actual
			new_proces = (t_proces *)ft_calloc(sizeof(t_proces), 1);
			if (!new_proces)
				return;
			new_proces->proces = all->token->wrd;
			if (current_proces == NULL)
			{
				// Si es el primer proceso, establece 'first_proces' como nuevo proceso
				first_proces = new_proces;
				current_proces = new_proces;
			}
			else
			{
				// Agregar el nuevo proceso a la lista de procesos existente
				current_proces->next = new_proces;
				current_proces = new_proces;
			}
		}
		else
		{
			// Avanzar al siguiente token
			all->token = all->token->next;
			if (current_proces != NULL)
			{
				// Cambiar de proceso cuando se encuentra una tubería
				current_proces = NULL;
			}
		}
		printf("proces: %s\n", new_proces->proces);
		all->token = all->token->next;
	}

	// Ahora 'first_proces' contiene la lista de procesos creada
}*/

