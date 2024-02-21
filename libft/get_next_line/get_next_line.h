/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:10:15 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:14:40 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft_get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		is_new_line(int fd, char *saves[]);

char	*get_line1(int fd, char *saves[]);

int		linelen(char *s, int stopatnl);

void	remove_line(int fd, char *saves[]);

void	add_line(int fd, char *saves[], char *read_line);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size);

int		handle_error(int nb_chars_read, char *saves[], int fd, char *read_line);

#endif