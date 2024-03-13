#include "../inc/minishell.h"

// Finds an executable file from the command and adds path if necessary
// Returns NULL if not found or no access
char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp_cmd;
	char	*tmp_path;
	int		index;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	index = 0;
	while (paths[index])
	{
		tmp_path = ft_strjoin(paths[index], "/");
		tmp_cmd = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(tmp_cmd, F_OK) == 0 && access(tmp_cmd, X_OK) == 0)
			return (tmp_cmd);
		free(tmp_cmd);
		index++;
	}
	return (NULL);
}

void	interpret_line(char *line, char *envp[])
{
	t_tokens	*tokens;
	t_list		*list_bag;
	t_list_cmd	*list_cmd;

	printf(NRM);
	if (!line)
		exit(0);
	rl_redisplay();
	tokens = NULL;
	list_bag = NULL;
	list_cmd = NULL;
	line = parse_env_var(line);
	parse(&tokens, line);
	if (syntax_check(tokens) == 0)
	{
		tokens = get_tokens(line);
		list_bag = get_bags_list(tokens);
		list_cmd = get_list_cmds_from_bags(list_bag, get_paths(envp));
		exec_commands(list_cmd, envp);
	}
}
