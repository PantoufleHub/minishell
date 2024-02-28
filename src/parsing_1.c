#include "../inc/minishell.h"

void	print_tokens(t_tokens *l_tokens)
{
	while (l_tokens)
	{
		printf("|%s|\n", l_tokens->token);
		l_tokens = l_tokens->next;
	}
}

void	add_token(t_tokens **l_tokens, char *token)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	new->token = token;
	new->next = NULL;
	if (!(*l_tokens))
		*l_tokens = new;
	else
	{
		tmp = *l_tokens;
		while ((tmp)->next)
			(tmp) = (tmp)->next;
		(tmp)->next = new;
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
	int		len;
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
	if (!(*string))
		*string = new;
	else
	{
		tmp = *string;
		while ((tmp)->next)
			(tmp) = (tmp)->next;
		(tmp)->next = new;
	}
}
