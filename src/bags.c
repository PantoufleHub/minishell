#include "../inc/minishell.h"

// count the token number in the list before processing it. Isn't used yet
int	token_count(t_tokens *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	add_cmd_node(t_list_cmd **cmds, t_cmd *st_cmd)
{
	t_list_cmd	*new;
	t_list_cmd	*current;

	new = malloc(sizeof(t_list_cmd));
	new->cmd = *st_cmd;
	new->next = NULL;
	current = NULL;
	if (*cmds == NULL)
		*cmds = new;
	else
	{
		current = *cmds;
		while (current->next != NULL)
			current = current->next;
	}
	current->next = new;
}

//doesn't work yet but is supposed to fill the cmd and cmd type to the structure cmd (st_cmd)
int	add_cmd_and_type(t_tokens *token, t_cmd *st_cmd, char **path)
{
	const char	*builtins[8] = {"echo", "cd", "pwd"
		,"export", "unset", "env", "exit", NULL};
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(token->token);
	st_cmd->cmd_type = CMD_EXTERNAL;
	st_cmd->cmd = get_cmd(path, token->token);
	while (builtins[i])
	{
		if (ft_strncmp(token->token, builtins[i], len) == 0
			&& ft_strncmp(token->token, builtins[i], ft_strlen(builtins[i])) == 0)
		{
			st_cmd->cmd_type = CMD_BUILTIN;
			st_cmd->cmd = ft_strdup(token->token);
		}
		i++;
	}
	if (!st_cmd->cmd)
		return (0);
	return (1);
}

void	store_chevron(t_cmd **cmd_st, t_tokens **token)
{
	if (ft_strncmp((*token)->token, "<", 1) == 0)
	{
		*token = (*token)->next;
		(*cmd_st)->infile = (*token)->token;
	}
	else if (ft_strncmp((*token)->token, ">>", 2) == 0)
	{
		(*cmd_st)->append = 1;
		*token = (*token)->next;
		(*cmd_st)->outfile = (*token)->token;
	}
	else if (ft_strncmp((*token)->token, ">", 1) == 0)
	{
		*token = (*token)->next;
		(*cmd_st)->outfile = (*token)->token;
	}
}

void	read_tokens(t_cmd *cmd_st, t_tokens **token, char **path)
{
	int cmd_found;

	cmd_found = 0;
	cmd_st->append = 0;
	cmd_st->infile = NULL;
	cmd_st->outfile = NULL;
	cmd_st->cmd = NULL;
	while (*token)
	{
		if (ft_strncmp((*token)->token, "|", 1) == 0)
			break ;
		store_chevron(&cmd_st, token);
		// if (ft_strncmp((*token)->token, "<<", 2) == 0)
		// {
		// 	HERE_DOC to do;
		// }
		// if (ft_strncmp(token->token, "args", 1) == 0)
		// 	do smth
		if (cmd_st->cmd == NULL || cmd_st->cmd[0] == '\0')
			cmd_found = add_cmd_and_type(*token, cmd_st, path);
		*token = (*token)->next;
	}
}

t_tokens	*get_tokens(char *line)
{
	t_tokens	*l_tokens;

	l_tokens = NULL;
	parse(&l_tokens, line);
	return (l_tokens);
}

void	init_cmd_struct(t_cmd *cmd)
{
	cmd->append = 0;
}

// int	main(int argc, char *argv[], char **env)
// {
// 	t_tokens	*l_tokens = NULL;
// 	char	**path = get_paths(env);
// 	t_cmd	st_cmd;

// 	if (argc != 2)
// 	{
// 		printf("Need 1 argument!\n");
// 		exit(0);
// 	}
// 	l_tokens = get_tokens(argv[1]);
// 	printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
// 	print_tokens(l_tokens);
// 	printf("~~~~~\n");

// 	read_tokens(&st_cmd, &l_tokens, path);
// 	printf("Command type : %d\n", st_cmd.cmd_type);
// 	printf("Command : %s\n", st_cmd.cmd);
// 	printf("Append mode: %d\n", st_cmd.append);
// 	printf("infile name: %s\n",st_cmd.infile);
// 	printf("outfile name: %s\n",st_cmd.outfile);
// 	free_tokens(l_tokens);
// 	return (0);
// }