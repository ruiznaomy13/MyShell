/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/21 16:11:02 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int arg_size(t_token *aux)
{
    int     i;

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

char **save_arg(t_all *all)
{
    t_token *aux;
    char    **str;
    int     i;

    aux = all->token;
    i = arg_size(aux);
    str = (char **)malloc(sizeof(char *) * (i + 1));
    if (!str)
        return (NULL);
    aux = all->token;
    i = 0;
    while (aux != NULL && aux->type != PIPE)
    {
        if (aux->type == RDOUT || aux->type == RDAP \
            || aux->type == RDIN || aux->type == RDHD)
                aux = aux->next->next;
        if (aux->wrd != NULL)
            str[i++] = aux->wrd;
        aux = aux->next;
    }
    str[i] = NULL;
    return (str);
}

// char    *env_search(char *str, char **env)
// {
//     char    *exp;
//     return (exp);
// }


void    create_process(t_all *all)
{
    t_process   *pcs;
    int         i;

    i = -1;
    pcs = (t_process *)ft_calloc(sizeof(t_token), 1);
    pcs->process = save_arg(all);
    printf("ARGUMENTS =");
    while (pcs->process[++i] != NULL)
    {
        printf(" %s ", pcs->process[i]);
    }
    printf("\n");
}

// 1. guardarm en el **char todo lo que no sea redirecccion ni su archivo
//    es decir, el siguiente token. [> file.txt]
// 2. Guardar el tipo texto dentro de un **char
// 3. Eliminamos los tokens que estan dentro del
//    a medida que los añadimos a la *cadena
// 4. Los demas tokens los guardamos dentro de una nueva lista con el tipo de
//    redireccion y el nombre del texto.
//     <<          hola             cat  -e  <    a      >     a      Makefile
// RD_HERE_DOC  HERE_DOC_LIMITER    ARG ARG  RD RD_FILE  RD  RD_FILE    ARG