#include "../inc/minishell.h"

void	clean_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->token);
		free(tokens);
		tokens = tmp;
	}
}
