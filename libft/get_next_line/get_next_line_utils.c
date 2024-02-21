/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:10:04 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 15:58:22 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_new_line(int fd, char *saves[])
{
	int	index;

	index = 0;
	if (!saves[fd])
		return (0);
	while (saves[fd][index])
	{
		if (saves[fd][index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

char	*get_line1(int fd, char *saves[])
{
	char	*line;
	int		len;
	int		index;

	if (!saves[fd])
		return (NULL);
	len = linelen(saves[fd], 1);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!saves[fd] || !line || len == 0)
		return (NULL);
	index = 0;
	while (index < len)
	{
		line[index] = saves[fd][index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

void	remove_line(int fd, char *saves[])
{
	int		nb_chars;
	int		total_chars;
	int		index;
	char	*temp;

	if (!saves[fd])
		return ;
	nb_chars = linelen(saves[fd], 1);
	total_chars = linelen(saves[fd], 0);
	if (nb_chars == total_chars)
	{
		free(saves[fd]);
		saves[fd] = NULL;
		return ;
	}
	index = total_chars - nb_chars;
	temp = (char *)malloc(sizeof(char) * (index + 1));
	temp[index] = '\0';
	while (index-- > 0)
		temp[index] = saves[fd][nb_chars + index];
	free(saves[fd]);
	saves[fd] = temp;
}

int	linelen(char *s, int stopatnl)
{
	int	length;

	length = 0;
	if (stopatnl)
	{
		while (s[length] != '\n' && s[length] != '\0')
			length++;
	}
	else
	{
		while (s[length] != '\0')
			length++;
	}
	if (s[length] == '\n' && stopatnl)
		length++;
	return (length);
}

void	add_line(int fd, char *saves[], char *read_line)
{
	int		length_save;
	int		length_read;
	char	*line;
	int		index;

	if (!saves[fd])
		length_save = 0;
	else
		length_save = linelen(saves[fd], 1);
	length_read = linelen(read_line, 0);
	line = (char *)malloc(sizeof(char) * (length_read + length_save + 1));
	index = 0;
	while (index++ < length_save)
		line[index - 1] = saves[fd][index - 1];
		index = 0;
	while (index++ < length_read)
		line[index + length_save - 1] = read_line[index - 1];
	line[index + length_save - 1] = '\0';
	free(saves[fd]);
	saves[fd] = line;
}
