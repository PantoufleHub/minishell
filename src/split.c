#include "../inc/minishell.h"

static size_t	word_count(const char *s, const char c)
{
	size_t	i;
	size_t	j;
	size_t	index;
	int	d_quote;
	int	s_quote;

	i = 0;
	j = 0;
	index = 0;
	d_quote = 0;
	s_quote = 0;
	while (s[i])
	{
		if (s[i] == 39 && !s_quote)
			d_quote = !d_quote;
		if (s[i] == 34 && !d_quote)
			s_quote = !s_quote;
		if (s[i] != c && index == 0)
		{
			index = 1;
			j++;
		}
		else if (s[i] == c && !d_quote && !s_quote)
			index = 0;
		i++;
	}
	return (j);
}

static char	*ft_buff(const char *str, size_t start, size_t end)
{
	char	*buff;
	int		i;

	i = 0;
	buff = (char *)malloc((end - start + 1) * sizeof(char));
	if (!buff)
		return (0);
	while (start < end)
		buff[i++] = str[start++];
	buff[i] = '\0';
	return (buff);
}

void	helper_split_2(size_t *i, size_t *j, int *s_quote, int *index)
{
	*i = 0;
	*j = 0;
	*s_quote = 0;
	*index = -1;
}

int	helper2_split_2(const char *s, char **split)
{
	if (!s)
		return (0);
	if (!split)
		return (0);
	return (1);
}

char	**ft_split_p(const char *s, const char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	int		s_quote;
	int		d_quote = 0;

	helper_split_2(&i, &j, &s_quote, &index);
	split = calloc((word_count(s, c) + 1), sizeof(char *));
	if (helper2_split_2(s, split) == 0)
		return (0);
	while (i <= strlen(s))
	{
		if (s[i] == 39 && !d_quote)
			s_quote = !s_quote;
		if (s[i] == 34 && !s_quote)
			d_quote = !d_quote;
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == strlen(s)) && index >= 0 && !s_quote && !d_quote)
		{
			split[j++] = ft_buff(s, index, i);
			index = -1;
		}
		i++;
	}
	return (split);
}
