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

int	store_chevron(t_cmd **cmd_st, t_tokens **token)
{
	if (ft_strncmp((*token)->token, "<", 1) == 0)
	{
		*token = (*token)->next;
		(*cmd_st)->infile = (*token)->token;
		return (1);
	}
	else if (ft_strncmp((*token)->token, ">>", 2) == 0)
	{
		(*cmd_st)->append = 1;
		*token = (*token)->next;
		(*cmd_st)->outfile = (*token)->token;
		return (1);
	}
	else if (ft_strncmp((*token)->token, ">", 1) == 0)
	{
		(*cmd_st)->append = 0;
		*token = (*token)->next;
		(*cmd_st)->outfile = (*token)->token;
		return (1);
	}
	return (0);
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

int	check_chev(t_tokens **token)
{
	printf("%s", (*token)->token);
	if (ft_strncmp((*token)->token, "<", 1) == 0)
		return (1);
	if (ft_strncmp((*token)->token, ">", 1) == 0)
		return (1);
	if (ft_strncmp((*token)->token, "<<", 2) == 0)
		return (1);
	if (ft_strncmp((*token)->token, ">>", 2) == 0)
		return (1);
	return (0);
}

void	init_cmd_st(t_cmd **new_cmd)
{
	(*new_cmd)->append = 0;
	(*new_cmd)->cmd = NULL;
	(*new_cmd)->cmd_type = 0;
	(*new_cmd)->infile = NULL;
	(*new_cmd)->outfile = NULL;
	(*new_cmd)->fd_in = STDIN_FILENO;
	(*new_cmd)->fd_out = STDOUT_FILENO;
}

void	fill_cmd_st(t_cmd *new_cmd, t_tokens *current_token, char **path)
{
	int	cmd_found;
	int	i;
	int	is_chevron;

	cmd_found = 0;
	i = 0;
	is_chevron = 0;
	init_cmd_st(&new_cmd);
	while (ft_strncmp(current_token->token, "|", 1) != 0)
	{
		is_chevron = store_chevron(&new_cmd, &current_token);
		// if (ft_strncmp(current_token->token, "<<", 2) == 0)
		// HERE_DOC to do;
		if (cmd_found)
		{
			if(is_chevron == 0)
				add_arg(new_cmd, current_token->token);
		}
		if (new_cmd->cmd == NULL || new_cmd->cmd[0] == '\0')
			cmd_found = add_cmd_and_type(current_token, new_cmd, path);
		current_token = current_token->next;
	}
}

t_list_cmd	*read_tokens(t_tokens *token, char **path)
{
	t_list_cmd	*list_cmd;
	t_list_cmd	*current_list_cmd;
	t_cmd		*new_cmd;

	list_cmd = NULL;
	current_list_cmd = NULL;
	new_cmd = NULL;
	while (token != NULL)
	{
		fill_cmd_st(new_cmd, token, path);
	}
	if (!list_cmd)
	{
		list_cmd = malloc(sizeof(t_list_cmd));
		list_cmd->cmd = *new_cmd;
		list_cmd->next = NULL;
		current_list_cmd = list_cmd;
	}
	else
	{
		current_list_cmd->next = malloc(sizeof(t_list_cmd));
		current_list_cmd = current_list_cmd->next;
		current_list_cmd->cmd = *new_cmd;
		current_list_cmd->next = NULL;
	}
	return (list_cmd);
}

t_tokens	*get_tokens(char *line)
{
	t_tokens	*l_tokens;

	l_tokens = NULL;
	parse(&l_tokens, line);
	return (l_tokens);
}

// int	main(int argc, char *argv[], char **env)
// {
// 	t_tokens	*l_tokens = NULL;
// 	char	**path = get_paths(env);
// 	// t_cmd	cmd_st = {0};

// 	if (argc != 2)
// 	{
// 		printf("Need 1 argument!\n");
// 		exit(0);
// 	}
// 	l_tokens = get_tokens(argv[1]);
// 	printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
// 	print_tokens(l_tokens);
// 	printf("~~~~~\n");

// 	t_list_cmd *list_cmd = read_tokens(&l_tokens, path);
// 	printf("Command type : %d\n", list_cmd->cmd.cmd_type);
// 	// printf("Command : %s\n", cmd_st.cmd);

// 	// t_list_arg *current_arg = cmd_st.args; // Use a temporary pointer for iteration
// 	// while (current_arg) {
// 	// 	printf("arguments : %s\n", current_arg->arg); // Print the current argument
// 	// 	current_arg = current_arg->next; // Move to the next argument
// 	// }
// 	// // printf("argument : %s\n", cmd_st.args[0]);
// 	// printf("Append mode: %d\n", cmd_st.append);
// 	// printf("infile name: %s\n",cmd_st.infile);
// 	// printf("outfile name: %s\n",cmd_st.outfile);
// 	free_tokens(l_tokens);
// 	return (0);
// }

To do:

typedef struct s_bag
{
	t_tokens	*tokens;
	struct s_bag	*next;
}	t_bag

t_list	*get_bags_list(t_tokens *token)
{
	t_list	*bags;
	t_bag	current_bag;
	while (token)
	{
		//ajoute token au bag
		//quand rencontre |, ajotue bag a list bags
		//recree un bag
	}
	return (bags);
}

t_cmd	*bags_to_cmd(t_bag *bag)
{
	//cree un t_cmd a partir d'un bag de token
}

t_list	*get_cmds_from_bag(t_list *bags)
{
	while(bags)
		bags_to_cmd(bags);
	return (t_list_cmd);
}

t_cmd_list	*get_cmds_from_tokens(t_tokens *token)
{
	t_list	bags = get_bags_list(token);
	t_cmd_list	cmds = get_cmds_from_bags(bags);
	return (cmds);
}