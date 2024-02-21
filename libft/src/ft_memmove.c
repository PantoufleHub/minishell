/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:58:27 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	int		index;

	if (!str1 && !str2)
		return (NULL);
	if (str2 < str1 && str2 + n > str1)
	{
		index = (int)n - 1;
		while (index >= 0)
		{
			((char *)str1)[index] = ((char *)str2)[index];
			index--;
		}
	}
	else
	{
		index = 0;
		while (index < (int)n)
		{
			((char *)str1)[index] = ((char *)str2)[index];
			index++;
		}
	}
	return (str1);
}
