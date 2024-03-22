#include "../inc/minishell.h"

void	signal_handler_child(int signum)
{
	signum = 0;
	if (signum == SIGINT)
		exit(0);
	else if (signum == SIGQUIT)
	{

	}
	else if (signum == SIGTERM)
	{

	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// printf("endsigint");
	}
	else if (signum == SIGQUIT)
	{
		// ft_printf("\n");
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

void	set_signals(void)
{
	// if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	// {
	// 	perror("Error registering SIGQUIT signal handler");
	// 	exit(EXIT_FAILURE);
	// }
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("Error registering SIGINT signal handler");
		exit(EXIT_FAILURE);
	}
	// if (signal(SIGTERM, signal_handler_child) == SIG_ERR)
	// {
	// 	perror("Error registering SIGTERM signal handler");
	// 	exit(EXIT_FAILURE);
	// }
}

void	set_signals_child(void)
{
	// if (signal(SIGQUIT, signal_handler_child) == SIG_ERR)
	// {
	// 	perror("Error registering SIGQUIT signal handler");
	// 	exit(EXIT_FAILURE);
	// }
	if (signal(SIGINT, signal_handler_child) == SIG_ERR)
	{
		perror("Error registering SIGINT signal handler");
		exit(EXIT_FAILURE);
	}
	// if (signal(SIGTERM, signal_handler_child) == SIG_ERR)
	// {
	// 	perror("Error registering SIGTERM signal handler");
	// 	exit(EXIT_FAILURE);
	// }
}
