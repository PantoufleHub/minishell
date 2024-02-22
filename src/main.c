#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		is_running;

	argv = NULL;
	argc = 0;
	set_signals();
	is_running = 1;
	while (is_running)
	{
		display_prompt();
		line = readline(" ");
		if (!line)
			is_running = 0;
		else
			interpret_line(line, envp);
		add_history(line);
		free(line);
	}
	ft_printf("\n");
	return (0);
}
