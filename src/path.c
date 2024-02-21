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
			full_path;
		}
	}
}