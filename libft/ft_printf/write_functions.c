/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:52:55 by aperron           #+#    #+#             */
/*   Updated: 2023/11/03 16:06:02 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_output_char(char c, int *counter)
{
	write(1, &c, 1);
	*counter += 1;
}

void	write_string(char *str, int *counter, int to_free)
{
	int	index;

	if (str == NULL)
		write_string("(null)", counter, 0);
	else
	{
		index = 0;
		while (str[index] != '\0')
		{
			write_output_char(str[index], counter);
			index++;
		}
	}
	if (to_free == 1)
		free(str);
}

void	write_number(long n, int *counter)
{
	if (n == 0)
	{
		write_output_char('0', counter);
		return ;
	}
	if (n < 0)
	{
		write_output_char('-', counter);
		n *= -1;
	}
	if (n > 9)
	{
		write_number(n / 10, counter);
		n %= 10;
	}
	if (n <= 9)
	{
		write_output_char(n + '0', counter);
	}
}

void	write_pointer(void *p, int *counter)
{
	char	*str;

	str = long_hexa((unsigned long long)p, "0123456789abcdef");
	write_string("0x", counter, 0);
	write_string(str, counter, 1);
}
