/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:49:51 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/22 19:49:52 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char* str_rep(char* source, char* target, char* replacement) {
    int sourceLength = ft_strlen(source);
    int targetLength = ft_strlen(target);
    int replacementLength = ft_strlen(replacement);
    int i;

    i = 0;
    char* result = NULL;
    int found = 0;
    while (i < sourceLength)
    {
        if (ft_strncmp(source + i, target, targetLength) == 0 && !found) {
            result = (char*)malloc(sourceLength + replacementLength - targetLength + 1);
            if (result == NULL)
                return (NULL);
            ft_strncpy(result, source, i);
            ft_strcpy(result + i, replacement);
            ft_strcpy(result + i + replacementLength, source + i + targetLength);
            found = 1;
        }
        i++;
    }
    if (!found)
        return strdup(source);
    return (result);
}

int main() {
    char    *originalString = "Este es un ejemplo de replace en C. replace esta palabra.";
    char    *searchString = "replace";
    char    *replacementString = "reemplazar";

    char    *replacedString = str_rep(originalString, searchString, replacementString);

    printf("Cadena original: %s\n", originalString);
    printf("Cadena reemplazada: %s\n", replacedString);

    free(replacedString);

    return 0;
}
