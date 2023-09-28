/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:35:19 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/28 15:55:57 by ncastell         ###   ########.fr       */
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

// str = string a buscar en el env
char *search_env(char *str, char *env[])
{
    int i;
    char *new;
    char *aux;

	i = -1;
    new = ft_strdup(str);
    aux = NULL;
    if (new == NULL)
        return NULL;
    new = ft_charjoin(new, '=');
    while (env[++i])
	{
        aux = ft_strnstr(env[i], new, ft_strlen(new));
        if (aux != NULL)
		{
            free(new);
            return (split_env(aux));
        }
    }
    free(new);
    return (NULL);
}

char *expand_var(t_token *tkn, char **env)
{
	int i;
	int flag;
	char *str;
	char *aux;
	char *var;

	i = 0;
	flag = 0;
	aux = "";
	var = NULL;
	str = ft_strdup(tkn->wrd);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag == 0)
		{
			if (str[i] == '\'')
				flag = COMMA_S;
			else
				flag = COMMA_D;
			i++;
		}
		else if ((str[i] == '\"' && flag == COMMA_D) || (str[i] == '\'' && flag == COMMA_S))
		{
			flag = 0;
			i++;
		}
		else if (str[i] == '$' && (flag == 0 || flag == COMMA_D))
		{
			var = search_var(&str[i]);
			if (search_env(var, env) != NULL)
				aux = ft_strjoin(aux, search_env(var, env));
			i += ft_strlen(var) + 1;
		}
		else {
			aux = ft_charjoin(aux, str[i]);
			i++;
		}
	}
	free(str);
	return (aux);
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
	pcs = (t_process *)ft_calloc(sizeof(t_process), 1);//num_process
	if (pcs == NULL)
		return ;
	pcs->process = save_arg(all);
	all->procesos = pcs;
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
