#include "../inc/minishell.h"

char	*find_paths(char *envp[])
{
	int	index;

	index = 0;
	while (envp[index] && ft_strncmp("PATH=", envp[index], 5))
		index++;
	return (envp[index] + 5);
}

// this function returns a tab of string that is equivalent to data->path of the function int path(t_data *data)
char	**get_paths(char *envp[])
{
	char	**paths;

	paths = ft_split(find_paths(envp), ':');
	if (!paths)
		error_message("Unable to find paths");
	return (paths);
}

int	path(t_data *data)
{
	const char	*path = getenv("PATH");
	char		*full_path;
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	full_path = ft_strdup("");
	data->path = ft_split(path, ':');
	while (data->path[i])
	{
		j = 0;
		while (j < data->n_cmd) //I need to find a way to count the number of commands read in read_line
		{
			tmp = ft_strjoin(data->path[i], "/");
			full_path = ft_strjoin(tmp, data->cmd[j].cmd); //I need to feed data->cmd[j].cmd
											//of commands somewhere in the line read by read_line
			free(tmp);
			if (access(full_path, X_OK) == 0)
			{
				free(data->cmd[j].cmd);
				data->cmd[j].cmd = full_path;
			}
			else
				free(full_path);
			j++;
		}
		i++;
	}
	i = 0;
	while (data->path[i])
	{
		free (data->path[i]);
		i++;
	}
	free (data->path);
	return (0);
}
