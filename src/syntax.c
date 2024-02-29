#include "../inc/minishell.h"

int	last_chevron(t_tokens *token)
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

int	chevron_meta(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
	if ((ft_strncmp(token->token, ">", 1) == 0
			|| ft_strncmp(token->token, "<", 1) == 0
			|| ft_strncmp(token->token, ">>", 2) == 0
			|| ft_strncmp(token->token, "<<", 2) == 0)
		&& ((ft_strncmp(token->token, ">", 1) == 0
			|| ft_strncmp(token->token, "<", 1) == 0
			|| ft_strncmp(token->token, ">>", 2) == 0
			|| ft_strncmp(token->token, "<<", 2) == 0
			||)
	}
}

int	pipo_syntax(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->token, "|", 1) == 0)
	{
		// printf("parse error\n");
		broken_pipe();
		return (EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	if ((ft_strncmp(token->token, "|", 1) == 0)
		&& !token->next)
	{
		// printf("parse error\n");
		broken_pipe();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(t_tokens *token)
{
	if (chevron_syntax(token) == 1)
		return (EXIT_FAILURE);
	if (pipo_syntax(token) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

