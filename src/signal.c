#include "../inc/minishell.h"

void	signal_handler(int signum)
{
	printf("\nRecieved signal: %d\n", signum);
	if (signum == 2)
		ft_printf("\n");
	if (signum == 3)
		abort();
}

void	set_signals(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
}