#include "../inc/minishell.h"

void	signal_handler_child(int signum)
{
	if (signum == SIGINT)
		exit(0);
	else if (signum == SIGQUIT)
	{
		exit(0);
	}
	else if (signum == SIGTERM)
	{
		exit(0);
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
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signals(void)
{
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		perror("Error registering SIGQUIT signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("Error registering SIGINT signal handler");
		exit(EXIT_FAILURE);
	}
}

void	set_signals_child(void)
{
	if (signal(SIGQUIT, signal_handler_child) == SIG_ERR)
	{
		perror("Error registering SIGQUIT signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, signal_handler_child) == SIG_ERR)
	{
		perror("Error registering SIGINT signal handler");
		exit(EXIT_FAILURE);
	}
}

void	sigterm(void)
{
	char	*prompt;

	prompt = get_prompt();
	printf("\033[F");
	printf("\033[G");
	printf("%sexit\n"NRM, prompt);
	free(prompt);
	exit(0);
}
