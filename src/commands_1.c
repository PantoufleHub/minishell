#include "../inc/minishell.h"

int	count_cmds(t_list_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

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

void	interpret_line(char *line, t_shell *shell)
{
	t_tokens	*tokens;
	t_list		*list_bag;
	t_list_cmd	*list_cmd;

	write(STDOUT_FILENO, NRM, ft_strlen(NRM));
	if (!line)
		exit(0);
	tokens = NULL;
	list_bag = NULL;
	list_cmd = NULL;
	line = parse_env_var(line, shell);
	if (syntax_check(tokens) == 0)
	{
		tokens = get_tokens(line);
		if (!tokens)
			return ;
		list_bag = get_bags_list(tokens);
		list_cmd = get_list_cmds_from_bags(list_bag, get_paths(shell->env));
		shell->fd_in = dup(STDIN_FILENO);
		shell->fd_out = dup(STDOUT_FILENO);
		exec_commands(shell, list_cmd);
	}
}
