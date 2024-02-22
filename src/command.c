#include "../inc/minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp_cmd;
	char	*tmp_path;
	int		index;

	index = 0;
	while (paths[index])
	{
		tmp_path = ft_strjoin(paths[index], "/");
		tmp_cmd = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(tmp_cmd, 0) == 0)
			return (tmp_cmd);
		free(tmp_cmd);
		index++;
	}
	return (NULL);
}

void	interpret_line(char *line, char *envp[])
{
	// char *testargv[] = {"-e", "test.txt", NULL};
	char *cmd;

	ft_printf("Recieved command: |%s|\n", line);
	cmd = get_cmd(get_paths(envp), line);
	if (!cmd)
		error_message("Failed to get command");
	else
		ft_printf("Got command: %s\n", cmd);
	// execve("/bin/cat/", testargv, envp);
}
