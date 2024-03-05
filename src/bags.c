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

//there may be a libft one working already. gotta check
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

void	add_arg(t_cmd *cmd_st, char *arg)
{
	t_list_arg	*new_arg;

	new_arg = malloc(sizeof(t_list_arg));
	if (!new_arg)
		return ;
	new_arg->arg = ft_strdup(arg);
	new_arg->next = NULL;
	if(cmd_st->args == NULL)
		cmd_st->args = new_arg;
	else
	{
		t_list_arg	*last = cmd_st->args;
		while(last->next != NULL)
			last = last->next;
		last->next = new_arg;
	}
}

void	read_tokens(t_cmd *cmd_st, t_tokens **token, char **path)
{
	int	cmd_found;
	int	i;

	cmd_found = 0;
	i = 0;
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
		if (cmd_found)
		{
			add_arg(cmd_st, (*token)->token);
		}
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
// 	t_cmd	cmd_st = {0};

// 	if (argc != 2)
// 	{
// 		printf("Need 1 argument!\n");
// 		exit(0);
// 	}
// 	l_tokens = get_tokens(argv[1]);
// 	printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
// 	print_tokens(l_tokens);
// 	printf("~~~~~\n");

// 	read_tokens(&cmd_st, &l_tokens, path);
// 	printf("Command type : %d\n", cmd_st.cmd_type);
// 	printf("Command : %s\n", cmd_st.cmd);

// 	t_list_arg *current_arg = cmd_st.args; // Use a temporary pointer for iteration
// 	while (current_arg) {
// 		printf("arguments : %s\n", current_arg->arg); // Print the current argument
// 		current_arg = current_arg->next; // Move to the next argument
// 	}
// 	// printf("argument : %s\n", cmd_st.args[0]);
// 	printf("Append mode: %d\n", cmd_st.append);
// 	printf("infile name: %s\n",cmd_st.infile);
// 	printf("outfile name: %s\n",cmd_st.outfile);
// 	free_tokens(l_tokens);
// 	return (0);
// }