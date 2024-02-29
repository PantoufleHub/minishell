#include "../inc/minishell.h"

int	syntax_check(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
		token = token->next;
	if ((ft_strncmp(token->token, ">", 1) == 0
			|| ft_strncmp(token->token, "<", 1) == 0
			|| ft_strncmp(token->token, ">>", 2) == 0
			|| ft_strncmp(token->token, "<<", 2) == 0)
		&& !token->next)
	{
		printf("parse error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	pipo_syntax(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->token, "|", 1) == 0)
	{
		printf("parse error\n");
		return (EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	if ((ft_strncmp(token->token, "|", 1) == 0)
		&& !token->next)
	{
		printf("parse error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}