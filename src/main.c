#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell			swagshell;
	char			*line;
	char			*prompt;

	init_shell(&swagshell, envp);
	while (argv[0] && argc)
	{
		set_signals();
		prompt = get_prompt();
		line = readline(prompt);
		interpret_line(line, &swagshell);
		add_history(line);
		free(prompt);
		free(line);
	}
	destroy_shell(&swagshell);
	return (0);
}
