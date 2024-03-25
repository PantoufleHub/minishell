#include "../inc/minishell.h"

void	clean_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->token)
			free(tokens->token);
		if (tokens)
			free(tokens);
		tokens = tmp;
	}
}
