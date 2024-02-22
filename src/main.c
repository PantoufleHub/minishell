#include "../inc/minishell.h"

int	main(void)
{
	char	*line;
	int		is_running;

	set_signals();
	is_running = 1;
	while (is_running)
	{
		display_prompt();
		line = readline("");
		if (!line)
			is_running = 0;
		else
			interpret_command(line);
		add_history(line);
		free(line);
	}
	return (0);
}
