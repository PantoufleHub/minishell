#include "../inc/minishell.h"

int	ft_cd(char **a_arg)
{
	if (!a_arg[1])
		return (EXIT_FAILURE);
	if (chdir(a_arg[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
