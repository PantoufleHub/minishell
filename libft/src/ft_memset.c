/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:07 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	index;
	char	*string;

	string = (char *) str;
	index = 0;
	while (index < n)
	{
		string[index] = c;
		index++;
	}
	return (str);
}
/*
int	main(void)
{
	char s[10];

	ft_memset(s, '0', sizeof(char) * 5);
	ft_memset(s + 5, '?', sizeof(char) * 5);
	for (int i = 0; i < 10; i++)
		printf("| %d,%c |", i, s[i]);
	return (0);
}*/
