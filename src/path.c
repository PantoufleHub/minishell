#include "../inc/minishell.h"

char	*find_paths(char *envp[])
{
	int	index;

	index = 0;
	while (envp[index] && ft_strncmp("PATH=", envp[index], 5))
		index++;
	return (envp[index] + 5);
}

char	**get_paths(char *envp[])
{
	char	**paths;

	paths = ft_split(find_paths(envp), ':');
	if (!paths)
		error_message("Unable to find paths");
	return (paths);
}

