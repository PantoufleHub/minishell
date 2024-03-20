#include "../inc/minishell.h"

char	*get_env(char **envp, char *var)
{
	int		index;
	char	*str;

	index = 0;
	str = malloc(ft_strlen(var) + 2);
	ft_strncpy(str, var, ft_strlen(var));
	str[ft_strlen(var)] = '=';
	str[ft_strlen(var)] = 0;
	while (envp[index] && ft_strncmp(str, envp[index], ft_strlen(str)))
		index++;
	if (envp[index])
		return (envp[index] + ft_strlen(str) + 1);
	return ("");
}

// lol flemme de corriger hihihi
char	*find_paths(char *envp[])
{
	return (get_env(envp, "PATH"));
}

char	**get_paths(char *envp[])
{
	char	**paths;

	paths = ft_split(find_paths(envp), ':');
	if (!paths)
		error_message("Unable to find paths");
	return (paths);
}

