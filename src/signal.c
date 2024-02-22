#include "../inc/minishell.h"

void	signal_handler(int signum)
{
	// printf("\nRecieved signal: %d\n", signum);
	if (signum == 2)
	{
		ft_printf("\n");
		display_prompt();
		// rl_on_new_line();
	}
	else if (signum == 3)
	{
		// NEED TO IMPLEMENT
		ft_printf("\n");
		exit(0);
	}
}

void	set_signals(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("Error registering CTRL+C signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		perror("Error registering CTRL+\\ signal handler");
		exit(EXIT_FAILURE);
	}
}
