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

t_tokens	*get_tokens(char *line)
{
	t_tokens	*l_tokens;

	l_tokens = NULL;
	if (parse(&l_tokens, line))
		return (l_tokens);
	return (NULL);
}
