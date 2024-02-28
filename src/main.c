#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	*prompt;

	set_signals();
	entry_display();
	while (argv[0] && argc)
	{
		prompt = get_prompt();
		line = readline(prompt);
		if (!line)
			kill(0, SIGTERM);
		interpret_line(line, envp);
		add_history(line);
		free(prompt);
		free(line);
	}
	return (0);
}
