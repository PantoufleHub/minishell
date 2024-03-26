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

void	sigterm(void)
{
	char	*prompt;

	prompt = get_prompt();
	printf("\033[F");
	printf("\033[G");
	printf("%sexit\n"NRM, prompt);
	free(prompt);
	exit(0);
}

void	clean_swag(t_list_cmd *list_cmd, t_list *list_bag,
	char **paths, t_tokens *tokens)
{
	free_arr_str(paths);
	clean_list_bag(list_bag);
	clean_list_cmd(list_cmd);
	clean_tokens(tokens);
}

void	interpret_line(char *line, t_shell *shell)
{
	t_tokens	*tokens;
	t_list		*list_bag;
	t_list_cmd	*list_cmd;
	char		**paths;
	char		*tmp_line;

	write(STDOUT_FILENO, NRM, ft_strlen(NRM));
	if (!line)
		sigterm();
	tokens = NULL;
	list_bag = NULL;
	list_cmd = NULL;
	paths = NULL;
	tmp_line = parse_env_var(line, shell);
	tokens = get_tokens(tmp_line);
	free(tmp_line);
	if (tokens && syntax_check(tokens) == 0)
	{
		paths = get_paths(shell->env);
		list_bag = get_bags_list(tokens);
		list_cmd = get_list_cmds_from_bags(list_bag, paths, shell);
		exec_commands(shell, list_cmd);
	}
	clean_swag(list_cmd, list_bag, paths, tokens);
}
