#include "../inc/minishell.h"

void	print_tokens(t_tokens *l_tokens)
{
	while (l_tokens)
	{
		printf("|%s| meta: %d\n", l_tokens->token, l_tokens->is_meta);
		l_tokens = l_tokens->next;
	}
}

int	check_meta(char *token)
{
	if (strncmp(token, "<", 1) == 0)
		return (1);
	if (strncmp(token, "<<", 2) == 0)
		return (1);
	if (strncmp(token, ">", 1) == 0)
		return (1);
	if (strncmp(token, ">>", 1) == 0)
		return (1);
	if (strncmp(token, "|", 1) == 0)
		return (1);
	return (0);
}

void	add_token(t_tokens **l_tokens, char *token, int meta)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	new->token = ft_strdup(token);
	new->is_meta = 0;
	if (check_meta(token))
		new->is_meta = 1;
	if (meta == 1)
		new->is_meta = 1;
	if (meta == 0)
		new->is_meta = 0;
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
	free_tokens(l_tokens);
	return (NULL);
}
