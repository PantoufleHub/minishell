#include "../inc/minishell.h"

void	free_string(t_string *string)
{
	t_string	*tmp;

	while (string)
	{
		tmp = string;
		string = string->next;
		free(tmp);
		tmp = NULL;
	}
}

int	string_len(t_string *string)
{
	int			len;

	len = 0;
	while (string)
	{
		string = string->next;
		len++;
	}
	return (len);
}

char	*get_string(t_string *string)
{
	char	*str;
	int		index;

	str = malloc(sizeof(char) * (string_len(string) + 1));
	index = 0;
	while (string)
	{
		str[index] = string->c;
		string = string->next;
		index++;
	}
	str[index] = 0;
	return (str);
}

void	add_char(t_string **string, char c)
{
	t_string	*new;
	t_string	*tmp;

	new = malloc(sizeof(t_string));
	new->c = c;
	new->next = NULL;
	tmp = NULL;
	if (!(*string))
		*string = new;
	else
	{
		tmp = *string;
		while ((tmp)->next)
		{
			(tmp) = (tmp)->next;
		}
		(tmp)->next = new;
	}
}
