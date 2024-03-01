#include "../inc/minishell.h"

int	token_count(t_tokens *token)
{
	int	count;

	count = 0;
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		count++;
		token = token->next;
	}
	count++;
	return (count);
}

/* int	baggin(t_tokens *token)
{
	char	**bag;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	bag == malloc((token_count(token) + 1) * sizeof(t_tokens));
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		if (ft_strncmp(token->token, "|", 1))
		{
			break ;
		}
		bag[i] = ft_strdup(token->token);
		token = token->next;
		i++;
	}
} */

//completement broken