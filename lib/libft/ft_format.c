/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:05:55 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 17:06:24 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_char(int c)
{
	return (write(2, &c, 1));
}

int	ft_put_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (write(2, "(null)", 6));
	}
	while (str[i])
	{
		if (write(2, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_put_nums(long int num, int ln)
{
	if (num < 0)
	{
		if (ft_put_char('-') == -1)
			return (-1);
		num *= -1;
		ln++;
	}
	if (num > 9)
	{
		ln = ft_put_nums(num / 10, ln);
		if (ln == -1)
			return (-1);
	}
	if (ft_put_char((num % 10) + '0') == -1)
		return (-1);
	ln++;
	return (ln);
}

int	ft_put_hex(unsigned int num, char type, int ln)
{
	char	*hex_val;

	if (type == 'X')
		hex_val = "0123456789ABCDEF";
	else
		hex_val = "0123456789abcdef";
	if (num > 15)
	{
		ln = ft_put_hex(num / 16, type, ln);
		if (ln == -1)
			return (-1);
	}
	if (ft_put_char(hex_val[num % 16]) == -1)
		return (-1);
	ln++;
	return (ln);
}

int	ft_put_pointer(unsigned long num, int ln)
{
	char	*pointer_val;

	pointer_val = "0123456789abcdef";
	if (num > 15)
	{
		ln = ft_put_pointer(num / 16, ln);
		if (ln == -1)
			return (-1);
	}
	if (ft_put_char(pointer_val[num % 16]) == -1)
		return (-1);
	ln++;
	return (ln);
}