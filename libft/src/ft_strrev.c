/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:59:36 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strrev(char *str)
{
	size_t	length;
	size_t	index;
	char	tmp;

	length = 0;
	while (str[length] != '\0')
		length++;
	index = 0;
	while (index < length / 2)
	{
		tmp = str[index];
		str[index] = str[length - index - 1];
		str[length - index - 1] = tmp;
		index++;
	}
}
