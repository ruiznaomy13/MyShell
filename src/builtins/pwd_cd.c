/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:51:55 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/12 19:10:19 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*strrcut(char *cadena, char caracter)
{
	char	*substring;
	char	*resultado;
	size_t	longitud;

	resultado = strrchr(cadena, caracter);
	if (resultado != NULL)
	{
		longitud = resultado - cadena;
		substring = malloc(longitud + 2);
		if (substring != NULL)
		{
			strncpy(substring, cadena, longitud + 1);
			substring[longitud + 1] = '\0';
			return (substring);
		}
	}
	return (NULL);
}

int	ft_pwd(void)
{
	printf( "%s\n", getcwd( NULL, 0 ));
	return (0);
}

int	ft_cd(t_process *pcs, t_all *all)
{
	char    *aux;
	char	*new_pwd;

	aux = getcwd(NULL, 0);
	new_pwd = "PWD ->";
	if (pcs->args[1][0] != '/')
	{
		if (chdir(ft_strjoin(ft_charjoin(aux, '/'), pcs->args[1])) == -1)
			ft_error(all, ACCESS_ERROR, "There was a problem accessing the directory");
	}
	else if (!ft_strcmp(pcs->args[1], ".."))
	{
		if (chdir(strrcut(pcs->args[1], '/')) == -1)
			ft_error(all, ACCESS_ERROR, "There was a problem accessing the directory");
	}
	else
	{
		if(chdir(pcs->args[1]) == -1)
			ft_error(all, ACCESS_ERROR, "There was a problem accessing the directory");
	}
	delete_env_var(&all->w_env, "PWD");
	save_var_env(ft_strjoin(new_pwd, getcwd(NULL, 0)), all);
	return (0);
}
