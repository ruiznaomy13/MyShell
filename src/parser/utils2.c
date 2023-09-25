/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:49:51 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/24 22:51:32 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
// #include <string.h>

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*save;
// 	size_t	len_s;

// 	if (!s)
// 		return (NULL);
// 	len_s = strlen(s);
// 	if (len > len_s - start)
// 		len = len_s - start;
// 	if (start >= len_s)
// 	{
// 		save = (char *)malloc(1);
// 		if (!save)
// 			return (NULL);
// 		save[0] = '\0';
// 		return (save);
// 	}
// 	save = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!save)
// 		return (NULL);
// 	while (start--)
// 		s++;
// 	strlcpy(save, s, len + 1);
// 	return (save);
// }

// char    *search_env(char *str, char *env[])
// {
// 	int i = 0;
// 	char *new;
// 	char *aux;

// 	new = strdup(str);
// 	aux = NULL;
// 	if (new == NULL)
// 		return NULL;
// 	strcat(new, "=");
// 	while (env[i] != NULL)
// 	{
// 		aux = strnstr(env[i], new, strlen(new));
// 		if (aux != NULL)
// 		{
// 			free(new); // Liberamos la memoria asignada a new
// 			return (aux);
// 		}
// 		i++;
// 	}
// 	free(new); // Liberamos la memoria asignada a new si no se encuentra
// 	return (NULL);
// }

// char *exp_var(char *str, char *env[])
// {
// 	char    *new;
// 	size_t     i;
    
// 	i = 0;
// 	new = search_env(str, env);
// 	if (new == NULL)
// 		return NULL;
// 	while (str[i] != '=')
// 		i++;
// 	return (ft_substr(new, strlen(str) + 1, strlen(new) - i));
// }

// char    *str_rep(char* source, char* target, char* replacement)
// {
//     int sourceLength = ft_strlen(source);
//     int targetLength = ft_strlen(target);
//     int replacementLength = ft_strlen(replacement);
//     int i;

//     i = 0;
//     char* result = NULL;
//     int found = 0;
//     while (i < sourceLength)
//     {
//         if (ft_strncmp(source + i, target, targetLength) == 0 && !found) {
//             result = (char*)malloc(sourceLength + replacementLength - targetLength + 1);
//             if (result == NULL)
//                 return (NULL);
//             strncpy(result, source, i);
//             strcpy(result + i, replacement);
//             strcpy(result + i + replacementLength, source + i + targetLength);
//             found = 1;
//         }
//         i++;
//     }   
//     printf("STR = %s\n", result);
//     if (!found)
//         return strdup(source);
//     return (result);
// }
