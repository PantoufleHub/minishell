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
		return (ft_strdup(cmd));
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

void	interpret_line_helper(t_tokens *tokens, t_shell *shell)
{
	char		**paths;
	t_list		*list_bag;
	t_list_cmd	*list_cmd;

	paths = NULL;
	list_cmd = NULL;
	list_bag = NULL;
	if (tokens && syntax_check(tokens) == 0)
	{
		paths = get_paths(shell->env);
		list_bag = get_bags_list(tokens);
		list_cmd = get_list_cmds_from_bags(list_bag, paths, shell);
		if (shell->heredocctrlc == 0)
			exec_commands(shell, list_cmd);
		else
			printf("\n");
	}
	clean_swag(list_cmd, list_bag, paths, tokens);
}

void	interpret_line(char *line, t_shell *shell)
{
	t_tokens	*tokens;
	char		*tmp_line;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, NRM, ft_strlen(NRM));
	shell->heredocctrlc = 0;
	if (!line)
		sigterm();
	tokens = NULL;
	tmp_line = parse_env_var(line, shell);
	tokens = get_tokens(tmp_line);
	free(tmp_line);
	interpret_line_helper(tokens, shell);
}
