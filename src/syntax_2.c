#include "../inc/minishell.h"

int	dub_pipo(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		if (ft_strncmp(token->token, "|", 1) == 0
			&& ft_strncmp(token->next->token, "|", 1) == 0)
		{
			broken_pipe();
			return (EXIT_FAILURE);
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
