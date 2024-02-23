#include "../inc/minishell.h"

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

void	helper_split_2(int *s_quote, int *index)
{
	*s_quote = 0;
	*index = -1;
}

int	helper2_split_2(const char *s, char **split, int *d_quote, t_dim *dim)
{
	*d_quote = 0;
	dim->x = 0;
	dim->y = 0;
	if (!s)
		return (0);
	if (!split)
		return (0);
	return (1);
}

void	quote_helper(const char *s, size_t x, int *s_quote, int *d_quote)
{
	if (s[x] == 39 && !*d_quote)
		*s_quote = !*s_quote;
	if (s[x] == 34 && !*s_quote)
		*d_quote = !*d_quote;
}

char	**ft_split_p(const char *s, const char c)
{
	t_dim	dim;
	int		index;
	char	**split;
	int		s_quote;
	int		d_quote;

	helper_split_2(&s_quote, &index);
	split = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (helper2_split_2(s, split, &d_quote, &dim) == 0)
		return (0);
	while (dim.x <= ft_strlen(s))
	{
		quote_helper(s, dim.x, &s_quote, &d_quote);
		if (s[dim.x] != c && index < 0)
			index = dim.x;
		else if ((s[dim.x] == c || dim.x == ft_strlen(s))
			&& index >= 0 && !s_quote && !d_quote)
		{
			split[dim.y++] = ft_buff(s, index, dim.x);
			index = -1;
		}
		dim.x++;
	}
	return (split);
}
