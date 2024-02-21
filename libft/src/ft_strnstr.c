/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:14:38 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index1;
	size_t	index2;

	index1 = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (!needle)
		return (NULL);
	while (index1 < len && haystack[index1] != '\0')
	{
		index2 = 0;
		while (needle[index2] == haystack[index1 + index2]
			&& index1 + index2 < len)
		{
			if (index2 == ft_strlen(needle) - 1)
				return ((char *)(haystack + index1));
			index2++;
		}
		index1++;
	}
	return (NULL);
}
