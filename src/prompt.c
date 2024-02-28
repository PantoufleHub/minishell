#include "../inc/minishell.h"

char	*get_prompt(void)
{
	char	*prompt;

	prompt = strjoin((char *[]){GRN"@swagminishell "CYN,
			getenv("USER"), "$: ", NRM, NULL});
	return (prompt);
}

void	display_prompt(void)
{
	char	*prompt;

	prompt = get_prompt();
	ft_printf(prompt);
	free(prompt);
}
