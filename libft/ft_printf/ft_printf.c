/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:16:30 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 15:04:04 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		nb_chars;
	int		index;
	int		to_interpret;
	va_list	args;

	to_interpret = 0;
	nb_chars = 0;
	index = 0;
	va_start(args, str);
	while (str[index] != '\0')
	{
		if (to_interpret == 1)
		{
			determine_output(str[index], args, &nb_chars);
			to_interpret = 0;
		}
		else if (str[index] == '%')
			to_interpret = 1;
		else
			write_output_char(str[index], &nb_chars);
		index++;
	}
	va_end(args);
	return (nb_chars);
}

// int	main(int argc, char const *argv[])
// {
// 	int me = 0;
// 	int you = 0;
// 	int	n = 10;
// 	int	*pn = &n;
// 	printf("\nNb chars: %i || Expected: %i\n", me, you);
// 	argc++;
// 	argv++;
// 	// int a = ft_printf(" %c ", '0');
// 	// int b = printf(" %c ", '0');

// 	// printf("\n%d %d\n", a, b);
// 	// printf("new change\n");
// 	return (0);
// }
