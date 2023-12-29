/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:51:55 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/29 16:40:09 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*strrcut(char	*cadena, char caracter)
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
	free(resultado);
	return (NULL);
}

int	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	search_dir(t_process *pcs, char	*aux)
{
	char	*aux_wrd;
	char	*aux_str;

	if (pcs->args[1][0] != '/')
	{
		aux_wrd = ft_charjoin(aux, '/');
		aux_str = ft_strjoin(aux_wrd, pcs->args[1]);
		if (chdir(aux_str) == -1)
		{
			free(aux_wrd);
			free(aux_str);
			return (-1);
		}
		free(aux_wrd);
		free(aux_str);
	}
	else
	{
		if (chdir(pcs->args[1]) == -1)
			return (-1);
	}
	return (0);
}

int	ft_cd(t_process *pcs, t_all *all)
{
	char	*aux;
	char	*new_pwd;
	char	*current_dir;
	char	*new_env;

	aux = getcwd(NULL, 0);
	new_pwd = ft_strdup("PWD=");
	current_dir = getcwd(NULL, 0);
	printf("llego aqui\n");
	if (!pcs->args[2] || search_dir(pcs, aux) == -1)
	{
		ft_error(all, ACCESS_ERROR, "Problem accessing the directory");
		free(new_pwd);
		free(current_dir);
		return (-1);
	}
	delete_env_var(&all->w_env, "PWD");
	new_env = ft_strjoin(new_pwd, current_dir);
	save_var_env(new_env, all);
	free(new_env);
	free(new_pwd);
	free(current_dir);
	return (0);
}
