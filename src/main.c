#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	char			*prompt;
	struct termios	save;

	set_signals();
	set_terminal(&save);
	entry_display();
	while (argv[0] && argc)
	{
		prompt = get_prompt();
		line = readline(prompt);
		interpret_line(line, envp);
		add_history(line);
		free(prompt);
		free(line);
	}
	restore_terminal(&save);
	return (0);
}
