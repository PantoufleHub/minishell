#include "../inc/minishell.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*cwd_np;

	cwd = ft_calloc(4096, sizeof(char));
	getcwd(cwd, 4096);
	cwd_np = ft_strrchr(cwd, '/') + 1;
	// CWD DOESNT UPDATE BY ITSELF!!
	prompt = strings_join((char *[]){RED, "@Swag"YEL"Shell:"GRN, getenv("USER"),
		" "CYN, cwd_np, BLU"/: ", MAG, NULL});
	free(cwd);
	return (prompt);
}

void	display_prompt(void)
{
	char	*prompt;

	prompt = get_prompt();
	ft_printf(prompt);
	free(prompt);
}
