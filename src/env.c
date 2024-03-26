#include "../inc/minishell.h"

int	ft_env(t_shell *shell)
{
	int		i;
	char	*equal;

	i = 0;
	equal = NULL;
	if (!shell->env)
		return (EXIT_FAILURE);
	while (shell->env[i])
	{
		equal = ft_strchr(shell->env[i], '=');
		if (equal)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
