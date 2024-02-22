#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	pid_t	child_pid;

	argv = NULL;
	argc = 0;
	set_signals();
	while (1)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			set_signals_child();
			line = readline(get_prompt());
			if (!line)
				kill(0, SIGTERM);
			interpret_line(line, envp);
			add_history(line);
			free(line);
			exit(0);
		}
		waitpid(child_pid, NULL, 0);
	}
	return (0);
}
