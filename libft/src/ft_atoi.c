/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:47:29 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:51:17 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	neg;
	int	value;

	index = 0;
	while (str[index] == '\n' || str[index] == '\r'
		|| str[index] == '\f' || str[index] == ' '
		|| str[index] == '\t' || str[index] == '\v')
		index++;
	neg = 1;
	if (str[index] == '-')
	{
		index++;
		neg = -1;
	}
	else if (str[index] == '+')
		index++;
	value = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		value = value * 10 + (str[index] - 48);
		index++;
	}
	return (value * neg);
}
