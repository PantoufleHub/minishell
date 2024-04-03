/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:48 by jbidaux           #+#    #+#             */
/*   Updated: 2024/04/03 14:45:33 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	entry_display(void)
{
	printf("\033[2J\033[H\n");
	ft_printf(CYN"\n\n  ██████   ██████  ███              ███          █████   "
		"            ████  ████ \n");
	ft_printf(" ░░██████ ██████  ░░░              ░░░          ░░███           "
		"    ░░███ ░░███ \n");
	ft_printf("  ░███░█████░███  ████  ████████   ████   █████  ░███████    ███"
		"███  ░███  ░███ \n");
	ft_printf("  ░███░░███ ░███ ░░███ ░░███░░███ ░░███  ███░░   ░███░░███  ███░"
		"░███ ░███  ░███ \n");
	ft_printf("  ░███ ░░░  ░███  ░███  ░███ ░███  ░███ ░░█████  ░███ ░███ ░████"
		"███  ░███  ░███ \n");
	ft_printf("  ░███      ░███  ░███  ░███ ░███  ░███  ░░░░███ ░███ ░███ ░███░"
		"░░   ░███  ░███ \n");
	ft_printf("  █████     █████ █████ ████ █████ █████ ██████  ████ █████░░███"
		"███  █████ █████\n");
	ft_printf("  ░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░"
		"░░░  ░░░░░ ░░░░░\n"NRM);
	ft_printf(RED"  v1.0.1 "YEL"Swagshell, "GRN"crafting "CYN"tomorrow's "BLU"s"
		"tandards.\n\n");
	ft_printf(MAG"                This project is brought to you by jbido and a"
		"péro\n\n\n"NRM);
}

void	error_message(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	exit_with_error(char *message)
{
	error_message(message);
	exit(1);
}

char	*strings_join(char **arr)
{
	char	*str;
	int		len;
	int		index_word;
	int		index_letter;

	len = 0;
	index_word = 0;
	while (arr[index_word])
		len += ft_strlen(arr[index_word++]);
	str = malloc(sizeof(char) * (len + 1));
	index_word = 0;
	index_letter = 0;
	while (arr[index_word])
	{
		ft_strlcpy(str + index_letter, arr[index_word],
			len);
		index_letter += ft_strlen(arr[index_word]);
		index_word++;
	}
	str[index_letter] = 0;
	return (str);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
