/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/21 11:26:29 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void    create_process(t_all *all)
{
    // t_process   *pcs;

    // pcs = (t_process *)ft_calloc(sizeof(t_token), 1);
    // if (!pcs)
    //     return (0);
    // if (type == TEXT)
    printf("CREATE PROCESS = %s\n", all->line);
}

// 1. guardarm een el **char todo lo que no sea redirecccion ni su archivo
//    es decir, el siguiente token. [> file.txt]
// 2. Guardar el tipo texto dentro de un **char
// 3. Eliminamos los tokens que estan dentro del
//    a medida que los añadimos a la *cadena
// 4. Los demas tokens los guardamos dentro de una nueva lista con el tipo de
//    redireccion y el nombre del texto.
//     <<          hola             cat  -e  <    a      >     a      Makefile
// RD_HERE_DOC  HERE_DOC_LIMITER    ARG ARG  RD RD_FILE  RD  RD_FILE    ARG
