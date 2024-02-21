#include "../inc/minishell.h"

int	main(void)
{
	char	*prompt;
	char	*line;
	int		is_running;

	set_signals();
	is_running = 1;
	while (is_running)
	{
		prompt = get_prompt();
		line = readline(prompt);
		if (!line)
			is_running = 0;
		else
			interpret_command(line);
		add_history(line);
		free(prompt);
		free(line);
	}
	return (0);
}
