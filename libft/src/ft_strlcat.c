/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:52:11 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	index;
	size_t	dst_size;
	size_t	src_size;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	index = 0;
	if (dst_size < n - 1 && n > 0)
	{
		while (dst_size + index < n - 1 && src[index] != '\0')
		{
			dst[index + dst_size] = src[index];
			index++;
		}
		dst[index + dst_size] = '\0';
	}
	if (dst_size > n)
		return (n + src_size);
	return (dst_size + src_size);
}
