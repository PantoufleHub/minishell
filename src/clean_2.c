#include "../inc/minishell.h"

void	clean_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->token)
		{
			free(tokens->token);
			tokens->token = NULL;
		}
		if (tokens)
		{
			free(tokens);
			tokens = NULL;
		}
		tokens = tmp;
	}
}
