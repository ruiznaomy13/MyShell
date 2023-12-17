/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/17 12:47:00 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all		all;

	(void)ac;
	(void)av;
	g_sig = 0;
	// signals();
	// sig_handler(sig_input);
	ft_bzero(&all, sizeof(t_all));
	list_env(&all, env);
	loop(&all);
	return (0);
}

char	*save_name(char *str)
{
	size_t	len;
	char	*name;
	
	if (!str)
		return (NULL);
	len = strlen(str);
	name = (char *)malloc((len + 2) * sizeof(char));
	if (!name)
		return (NULL);
	strcpy(name, str);
	name[len] = '>';
	name[++len] = '\0';
	return (name);
}

void	mostra_tokens(t_all *all)
{
	int			i;
	t_token		*aux;

	i = 1;	
	aux = all->token;
	while (aux != NULL)
	{
		printf("%d = %s -> %d\n", i, aux->wrd, aux->type);
		aux = aux->next;
		i++;
	}
}

void	mostra_rd(t_process *pcs)
{
	int			i;
	t_token		*aux;

	i = 1;
	aux = pcs->rd;
	printf("REDIRECCIONES =\n");
	if (!aux){
		printf("no hi ha redi(mostra redi)\n");
		return ;
	}
	while (aux != NULL)
	{
		printf("%d = %s -> %d\n", i, aux->wrd, aux->type);
		aux = aux->next;
		i++;
		if (i == 10)
			return ;
	}
}

void	mostra_process(t_all *all)
{
	int			i;
	int			j;
	t_process	*aux;

	j = 1;
	aux = all->prcs;
	while (aux != NULL)
	{
		i = -1;
		printf("\n\nPROCESS %d =\n", j);
		while (aux->args && aux->args[++i] != NULL)
			printf("[%s] ", aux->args[i]);
		printf("\n");
		if (aux->rd)
			mostra_rd(aux);
		j++;
		aux = aux->next;
	}
}

void	ft_free_all(t_all *all)
{
	t_token		*tkn;
	t_token		*rd;
	t_process	*prc;

	while (all->prcs != NULL && all->prcs->rd != NULL)
	{
		rd = all->prcs->rd;
		all->prcs->rd = all->prcs->rd->next;
		free(rd);
	}
	while (all->prcs != NULL)
	{
		prc = all->prcs;
		all->prcs = all->prcs->next;
		free(prc);
	}
	while (all->token != NULL)
	{
		tkn = all->token;
		all->token = all->token->next;
		free(tkn);
	}
	// printf("Free hecho.\n");
}
