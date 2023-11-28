/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:30:54 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/28 18:32:51 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int	main(void)
{
	char	*texto = "/System/Volumes/Data/sgoinfre/Perso/ncastell/main_miniShell";
	char	caracter = '/';

	texto = strrcut(texto, caracter);

	if (substring != NULL) {
		printf(" '%c': %s\n", caracter, substring);
		free(substring); // Liberar la memoria asignada
	} else {
		printf("El caracter no fue encontrado en la cadena o hubo un error.\n");
	}

	return 0;
}
