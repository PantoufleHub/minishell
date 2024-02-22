#include "../inc/minishell.h"

void	error_message(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	exit_with_error(char *message)
{
	error_message(message);
	exit(1);
}
