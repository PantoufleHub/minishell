#include "../inc/minishell.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*name;
	char	*pwd;
	char	*home;

	name = getenv("USER");
	pwd = getenv("PWD");
	home = getenv("HOME");
	prompt = ft_strjoin(name, ": ");
	return (prompt);
}
