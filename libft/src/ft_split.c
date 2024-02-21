/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:29:35 by aperron           #+#    #+#             */
/*   Updated: 2023/12/14 16:52:55 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	nb_words(const char *str, char c)
{
	int	count;
	int	index;
	int	in_word;

	index = 0;
	count = 0;
	in_word = 0;
	while (str[index] != '\0')
	{
		if (str[index] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (str[index] == c)
			in_word = 0;
		index++;
	}
	return (count);
}

static char	*strdup(const char *str, int start, int end)
{
	char	*word;
	int		index;

	index = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start + index < end)
	{
		word[index] = str[start + index];
		index++;
	}
	word[index] = '\0';
	return (word);
}

static char	**free_all(char **split)
{
	int	index;

	index = 0;
	while (split[index] != NULL)
	{
		free(split[index]);
		split[index] = NULL;
		index++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	index;
	size_t	word_index;
	int		word_start;
	char	**split;

	split = malloc((nb_words(s, c) + 1) * sizeof(char *));
	if (!s || !(split))
		return (0);
	index = -1;
	word_index = 0;
	word_start = -1;
	while (++index <= ft_strlen(s))
	{
		if (s[index] != c && word_start < 0)
			word_start = index;
		else if ((s[index] == c || index == ft_strlen(s)) && word_start >= 0)
		{
			split[word_index] = strdup(s, word_start, index);
			if (!split[word_index++])
				return (free_all(split));
			word_start = -1;
		}
	}
	split[word_index] = NULL;
	return (split);
}
