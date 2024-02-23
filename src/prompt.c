#include "../inc/minishell.h"

void	display_prompt(void)
{
	char	*user;
	char	*pwd;
	char	*home;

	user = getenv("USER");
	pwd = getenv("PWD");
	home = getenv("HOME");
	ft_printf(CYN "%s: " YEL "%s$ " NRM, pwd, user);
}

char	*get_prompt(void)
{
	return (CYN"STILL A FUCKING PLACEHOLDER: "NRM);
}
