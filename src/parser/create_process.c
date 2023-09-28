/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/28 23:29:41 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	arg_size(t_token *tkn)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = tkn;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == RDOUT || aux->type == RDAP \
			|| aux->type == RDIN || aux->type == RDHD)
			aux = aux->next;
		aux = aux->next;
		i++;
	}
	return (i);
}

void	add_rd(t_token *rd, t_all *all)
{
	t_token*	aux;

	if (all->prcs->rd == NULL)
		all->prcs->rd = rd;
	else
	{
		aux = all->prcs->rd;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = rd;
	}
}

void list_redirection(t_all *all)
{
    t_token	*rd;
	t_token	*aux;

	aux = all->token;
	rd = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!rd)
		return ;
	while (aux != NULL)
	{
		if (aux->type == RDOUT || aux->type == RDAP \
		 || aux->type == RDIN || aux->type == RDHD)
		 {
			rd->type = aux->type;
			rd->wrd = aux->next->wrd;
			aux = aux->next;
		 }
		 aux = aux->next;
	}
	add_rd(rd, all);
}

char **save_arg(t_all *all)
{
	char    **str;
	t_token	*aux;
	int     i;

	aux = all->token;
	str = (char **)malloc(sizeof(char *) * (arg_size(all->token) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == RDOUT || aux->type == RDAP || aux->type == RDIN || aux->type == RDHD)
			aux = aux->next; 
		else if (aux->wrd != NULL)
		{
			aux->wrd = expand_var(aux, all->env);
			str[i++] = aux->wrd;
		}
		aux = aux->next;
	}
	return (str);
}

void	create_process(t_all *all)
{
	int			i;
	t_process	*pcs = NULL;

	i = -1;
	pcs = (t_process *)ft_calloc(sizeof(t_process), 1);
	if (pcs == NULL)
		return ;
	pcs->args = save_arg(all);
	list_redirection(all);
	all->prcs = pcs;
}

// void	list_process(t_all *all)
// {
// 	int	i;

// 	i = 0;
// 	while (all->num_process <= i)
// 	{
// 		create_process(&all);
// 		i++;
// 	}
	
// }

// 1. guardarm en el **char todo lo que no sea redirecccion ni su archivo
//    es decir, el siguiente token. [> file.txt]
// 2. Guardar el tipo texto dentro de un **char
// 3. Eliminamos los tokens que estan dentro del
//    a medida que los añadimos a la *cadena
// 4. Los demas tokens los guardamos dentro de una nueva lista con el tipo de
//    redireccion y el nombre del texto.
//     <<          hola             cat  -e  <    a      >     a      Makefile
// RD_HERE_DOC  HERE_DOC_LIMITER    ARG ARG  RD RD_FILE  RD  RD_FILE    ARG
