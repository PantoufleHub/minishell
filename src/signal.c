#include "../inc/minishell.h"

void	signal_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		exit(0);
	}
	else if (signum == SIGQUIT)
		exit(0);
	else if (signum == SIGTERM)
		exit(0);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{}
	else if (signum == SIGQUIT)
		exit(0);
	else if (signum == SIGTERM)
		exit(0);
}

void	set_signals(void)
{
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
}

void	set_signals_child(void)
{
	if (signal(SIGQUIT, signal_handler_child) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, signal_handler_child) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
}
