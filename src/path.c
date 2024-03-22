#include "../inc/minishell.h"

char	*get_env(char **envp, char *var)
{
	int		index;
	char	*str;
	int		len;

	index = 0;
	str = malloc(ft_strlen(var) + 2);
	ft_strncpy(str, var, ft_strlen(var));
	str[ft_strlen(var)] = '=';
	str[ft_strlen(var)] = 0;
	len = ft_strlen(str);
	while (envp[index] && ft_strncmp(str, envp[index], len))
		index++;
	free(str);
	if (envp[index])
		return (envp[index] + len + 1);
	return ("");
}

char	*find_paths(char *envp[])
{
	return (get_env(envp, "PATH"));
}

char	**get_paths(char *envp[])
{
	char	**paths;
	char	*find_path;

	find_path = NULL;
	find_path = find_paths(envp);
	paths = ft_split(find_path, ':');
	// free (find_path);
	if (!paths)
		error_message("Unable to find paths");
	return (paths);
}
