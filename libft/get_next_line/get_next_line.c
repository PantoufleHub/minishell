/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:10:12 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 15:58:13 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*saves[4096];
	char		*line;
	char		*read_line;
	int			nb_chars_read;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE < 1)
		return (NULL);
	nb_chars_read = -1;
	while (!is_new_line(fd, saves) || nb_chars_read == 0)
	{
		read_line = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		nb_chars_read = read(fd, read_line, BUFFER_SIZE);
		if (handle_error(nb_chars_read, saves, fd, read_line))
			return (NULL);
		if (nb_chars_read == 0)
		{
			free(read_line);
			break ;
		}
		add_line(fd, saves, read_line);
		free(read_line);
	}
	line = get_line1(fd, saves);
	remove_line(fd, saves);
	return (line);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	else
		ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	index;

	str = (char *)s;
	index = 0;
	while (index < n)
	{
		str[index] = '\0';
		index++;
	}
}

int	handle_error(int nb_chars_read, char *saves[], int fd, char *read_line)
{
	if (nb_chars_read < 0)
	{
		free(saves[fd]);
		saves[fd] = NULL;
		free(read_line);
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char	*file1 = "test1.txt";
// 	char	*file2 = "test2.txt";
// 	int		fd = open(file1, O_RDONLY);
// 	int		fd2 = open(file2, O_RDONLY);
// 	// int fds[2] = {fd, fd2};
// 	// char *buffer;
// 	// int nb_read;
// 	// int i = 0;

// 	char *line;
// 	int i = 0;
// 	while (i++ < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("Line %i: |%s|\n", i, line);
// 	}
// 	// while (i++ < 10)
// 	// {
// 	// 	buffer = (char *)calloc(20, sizeof(char));
// 	// 	nb_read = read(fds[i%2], buffer, 5);
// 	// 	printf("Read: %s\n%i chars read\n", buffer, nb_read);
// 	// }

// 	return 0;
// }