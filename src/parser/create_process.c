/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/28 21:00:06 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	arg_size(t_token *aux)
{
	int		i;

	i = 0;
	while (aux != NULL && aux->type != PIPE)
	{
		if (aux->type == RDOUT || aux->type == RDAP \
			|| aux->type == RDIN || aux->type == RDHD)
			aux = aux->next->next;
		aux = aux->next;
		i++;
	}
	return (i);
}

void remove_tkn(t_all *all)
{
    t_token *next_token;
	
    if (all == NULL || all->token == NULL)
        return;
    next_token = all->token->next;
    if (all->token->wrd != NULL)
        free(all->token->wrd);
    free(all->token);
    all->token = next_token;
}


char **save_arg(t_all *all)
{
	char    **str;
	int     i;

	i = arg_size(all->token);
	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (all->token != NULL && all->token->type != PIPE)
	{
		if (all->token->type == RDOUT || all->token->type == RDAP \
			|| all->token->type == RDIN || all->token->type == RDHD)
				all->token = all->token->next->next;
		if (all->token->wrd != NULL)
		{
			all->token->wrd = expand_var(all->token, all->env);
			str[i++] = all->token->wrd;
		}
		all->token = all->token->next;
		// remove_tkn(all);
	}
	return (str);
}

void	create_process(t_all *all)
{
	int			i;
	t_process	*pcs = NULL;

	i = -1;
	pcs = (t_process *)ft_calloc(sizeof(t_process), 1);//num_process
	if (pcs == NULL)
		return ;
	pcs->args = save_arg(all);
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
