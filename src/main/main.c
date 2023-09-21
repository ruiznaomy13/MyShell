/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:27 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/21 13:32:07 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_all		all;
	int			coma;

	(0 || (ac = 0) || (av = 0) || (env = 0));
	ft_bzero(&all, sizeof(t_all));
	while (42)
	{
		all.line = readline("myshell🌞> ");
		add_history(all.line);
		printf("%s\n", all.line);

		coma = check_cometes(all.line);
		if (coma == 34 || coma == 39)
		{
			printf("ERROR %i\n", coma);
			exit (1);
		}
		else
		{
			printf("Funca teoricament\n");
			// exit (1);
			// ft_errors(); TODO
			lexer(&all);
			// printf("abans create proces\n");
			//create_proces(&all);
			// printf("despres create proces\n");
			mostra_tokens(&all);
			//mostra_proces(&all);
		}


		ft_free(&all);
	}
	return (0);
}

void	mostra_tokens(t_all *all)
{
	int			i;
	t_token		*aux;

	i = 1;
	aux = all->token;
	while (aux != NULL)
	{
		printf("%d = %s\n", i, aux->wrd);
		aux = aux->next;
		i++;
	}
}

// void	mostra_proces(t_all *all)
// {
// 	int			i;
// 	t_proces	*aux;

// 	i = 1;
// 	aux = all->procesos;
// 	while (aux != NULL)
// 	{
// 		printf("%d = %s\n", i, aux->proces);
// 		aux = aux->next;
// 		i++;
// 	}
// }

void	ft_free(t_all *all)
{
	t_token		*tkn;
	// t_proces	*prc;

	while (all->token != NULL)
	{
		tkn = all->token;
		all->token = all->token->next;
		free(tkn);
	}
	// while (all->procesos != NULL)
	// {
	// 	prc = all->procesos;
	// 	all->procesos = all->procesos->next;
	// 	free(tkn);
	// }
}
