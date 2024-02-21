/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:31:42 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	math_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	reverse_string(char *str)
{
	size_t	length;
	size_t	index;
	char	tmp;

	length = ft_strlen(str);
	index = 0;
	while (index < length / 2)
	{
		tmp = str[index];
		str[index] = str[length - index - 1];
		str[length - index - 1] = tmp;
		index++;
	}
}

static int	int_length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	int		index;

	str = (char *)malloc(sizeof(char) * (int_length(n) + 1));
	if (!str)
		return (NULL);
	is_neg = n < 0;
	index = 0;
	if (n == 0)
		str[index++] = '0';
	else
	{
		while (n != 0)
		{
			str[index++] = math_abs(n % 10) + '0';
			n /= 10;
		}
		if (is_neg)
			str[index++] = '-';
	}
	str[index] = '\0';
	reverse_string(str);
	return (str);
}
