#include "../inc/minishell.h"

t_data	parsing(char *line)
{
	t_data	data;

	data.trim = trim_sp(ft_split_p(line, ' '));
	data.cmd[0].split = ft_split_p(line, ' ');
	data.cmd[0].cmd = data.cmd[0].split[0];
	return (data);
}
