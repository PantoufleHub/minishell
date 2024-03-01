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
	// char *testargv[] = {"-e", "test.txt", NULL};
	char		*cmd;
	t_tokens	*tokens;

	tokens = NULL;
	printf("\n"MAG SEP NRM);
	ft_printf(YEL"Received line:\n"NRM"|%s|\n", line);
	if (!line)
		return ;
	cmd = get_cmd(get_paths(envp), line);
	if (!cmd)
		error_message(RED"Failed to get command"NRM);
	else
		ft_printf(GRN"Got command: "NRM"%s\n", cmd);
	printf("\n");
	parse(&tokens, line);
	ft_printf(YEL"Got tokens:\n"NRM);
	print_tokens(tokens);
	syntax_check(tokens);
	printf("\n");
	printf(YEL"Line with environment variables: "NRM"\n%s\n", parse_env_var(line));
	printf(MAG SEP"\n"NRM);
	// printf("%d", token_count(tokens));
}
