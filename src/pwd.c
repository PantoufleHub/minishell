#include "../inc/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free (cwd);
	return (EXIT_SUCCESS);
}
