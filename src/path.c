#include "../inc/minishell.h"

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
		while (j < data->n_cmd)
		{
			tmp = ft_strjoin(data->path[i], "/");
			full_path = ft_strjoin(tmp, data->cmd[j].cmd);
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