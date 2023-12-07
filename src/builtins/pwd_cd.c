/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:51:55 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/07 13:52:34 by mmonpeat         ###   ########.fr       */
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

int	ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	ft_cd(t_process *pcs, t_all *all)
{
	char    *aux;
	char	*new_pwd;

	aux = getcwd(NULL, 0);
	new_pwd = "PWD ->";
	if (pcs->args[1][0] != '/')
		chdir(ft_strjoin(ft_charjoin2(aux, '/'), pcs->args[1]));
	else if (!ft_strcmp(pcs->args[1], ".."))
		chdir(strrcut(pcs->args[1], '/'));
	else
		chdir(pcs->args[1]);
	delete_env_var(&all->w_env, "PWD");
	printf("NEW PWD = %s\n", ft_strjoin(new_pwd, getcwd(NULL, 0)));
	save_var_env(ft_strjoin(new_pwd, getcwd(NULL, 0)), all);
	return (0);
}