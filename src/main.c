#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	*prompt;
	pid_t	child_pid;

	set_signals();
	entry_display();
	while (argv[0] && argc)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			set_signals_child();
			prompt = get_prompt();
			line = readline(prompt);
			if (!line)
				kill(0, SIGTERM);
			interpret_line(line, envp);
			add_history(line);
			free(prompt);
			free(line);
			exit(0);
		}
		waitpid(child_pid, NULL, 0);
	}
	return (0);
}
