#include "../inc/minishell.h"

size_t	word_count(const char *s, const char c)
{
	size_t	j;
	size_t	index;
	int		d_quote;
	int		s_quote;

	j = 0;
	index = 0;
	d_quote = 0;
	s_quote = 0;
	while (*s)
	{
		if (*s == 39 && !s_quote)
			d_quote = !d_quote;
		if (*s == 34 && !d_quote)
			s_quote = !s_quote;
		if (*s != c && index == 0)
		{
			index = 1;
			j++;
		}
		else if (*s == c && !d_quote && !s_quote)
			index = 0;
		s++;
	}
	return (j);
}

char	*trim_sp(char	**split)
{
	char	*line;
	char	*tmp;
	char	*sp;
	int		i;
	int		count;

	i = 0;
	count = 0;
	sp = ft_strdup("");
	while (split[i++])
		count++;
	i = 0;
	while (i < count)
	{
		tmp = line;
		if (i > 0)
			sp = ft_strjoin(line, " ");
		tmp = ft_strjoin(sp, split[i]);
		if (i > 0)
			free (sp);
		line = tmp;
		free (tmp);
		i++;
	}
	return (line);
}
