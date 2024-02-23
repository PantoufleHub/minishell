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
