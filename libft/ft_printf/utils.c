/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:40:49 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 15:19:24 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*long_hexa(unsigned long long n, char *base)
{
	char	*hexa;
	int		index;
	int		n2;

	index = 0;
	n2 = n;
	hexa = (char *)malloc(sizeof(char) * (30));
	if (n != 0)
	{
		while (n != 0)
		{
			hexa[index++] = base[n % 16];
			n /= 16;
		}
	}
	else
		hexa[index++] = '0';
	hexa[index] = '\0';
	ft_strrev(hexa);
	return (hexa);
}

void	determine_output(char format, va_list args, int *counter)
{
	char	*str;

	if (format == '%')
		write_output_char('%', counter);
	if (format == 'c')
		write_output_char(va_arg(args, int), counter);
	if (format == 's')
		write_string(va_arg(args, char *), counter, 0);
	if (format == 'd' || format == 'i')
		write_number(va_arg(args, int), counter);
	if (format == 'u')
		write_number(va_arg(args, unsigned int), counter);
	if (format == 'x')
	{
		str = long_hexa(va_arg(args, unsigned int), "0123456789abcdef");
		write_string(str, counter, 1);
	}
	if (format == 'X')
	{
		str = long_hexa(va_arg(args, unsigned int), "0123456789ABCDEF");
		write_string(str, counter, 1);
	}
	if (format == 'p')
		write_pointer(va_arg(args, void *), counter);
}
