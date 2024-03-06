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
	new->cmd = st_cmd;
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
		list_cmd->cmd = new_cmd;
		list_cmd->next = NULL;
		current_list_cmd = list_cmd;
	}
	else
	{
		current_list_cmd->next = malloc(sizeof(t_list_cmd));
		current_list_cmd = current_list_cmd->next;
		current_list_cmd->cmd = new_cmd;
		current_list_cmd->next = NULL;
	}
	return (list_cmd);
}

t_cmd	*bag_to_cmd(t_tokens *bag, char **path)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_cmd_st(&cmd);
	bag = NULL;
	path = NULL;
	return(cmd);
}

t_list	*get_bags_list(t_tokens *tokens)
{
	t_list		*bags;
	t_list		*current_bag;
	t_tokens	*current_tokens;

	bags = NULL;
	current_bag = NULL;
	current_tokens = NULL;
	while (tokens != NULL)
	{
		current_tokens = NULL;
		while (tokens != NULL && !(ft_strncmp(tokens->token, "|",1) == 0))
		{
			add_token(&current_tokens, tokens->token);
			tokens = tokens->next;
		}
		current_bag = ft_lstnew(current_tokens);
		ft_lstadd_back(&bags, current_bag);
		if (tokens != NULL && ft_strncmp(tokens->token, "|", 1) == 0)
			tokens = tokens->next;
	}
	return (bags);
}

t_list_cmd	*get_list_cmds_from_bags(t_list *bags, char **path)
{
	t_list_cmd	*cmds;
	t_list_cmd	*last_node;
	t_list_cmd	*new_node;

	cmds = NULL;
	last_node = NULL;
	new_node = NULL;
	while (bags)
	{
		new_node = malloc(sizeof(t_list_cmd));
		new_node->next = NULL;
		new_node->cmd = bag_to_cmd((t_tokens *)bags->content, path);
		if (!cmds)
		{
			cmds = new_node;
			last_node = new_node;
		}
		else
		{
			last_node->next = new_node;
			last_node = last_node->next;
		}
		bags = bags->next;
	}
	return (cmds);
}

t_list_cmd	*get_cmds_from_tokens(t_tokens *tokens, char **path)
{
	t_list		*bags;
	t_list_cmd	*cmds;

	bags = get_bags_list(tokens);
	cmds = get_list_cmds_from_bags(bags, path);
	return (cmds);
}

t_tokens	*get_tokens(char *line)
{
	t_tokens	*l_tokens;

	l_tokens = NULL;
	parse(&l_tokens, line);
	return (l_tokens);
}

void print_bag_contents(t_list *bags) {
    while (bags) {
        t_tokens *tokens_in_bag = (t_tokens *)(bags->content); // Correct casting

        while (tokens_in_bag) {
            printf("%s\n", tokens_in_bag->token);
            tokens_in_bag = tokens_in_bag->next;
        }
		printf("------\n");
        bags = bags->next; // Move to the next bag
    }
}

void print_list_cmds(t_list_cmd *list_cmd) {
    t_list_cmd *current = list_cmd; // Start with the first node in the list

    // Iterate over each node in the list
    while (current != NULL) {
        t_cmd *cmd = current->cmd; // Get the command structure from the current node

        // Print command type
        printf("Command type: %d\n", cmd->cmd_type);

        // Print command
        if (cmd->cmd != NULL) {
            printf("Command: %s\n", cmd->cmd);
        }

        // // Print arguments
        // t_list_arg *current_arg = cmd->args;
        // printf("Arguments:");
        // while (current_arg != NULL) {
        //     if (current_arg->arg != NULL) {
        //         printf(" %s", current_arg->arg);
        //     }
        //     current_arg = current_arg->next;
        // }
        printf("\n");

        // Print infile and outfile
        if (cmd->infile != NULL) {
            printf("Input file: %s\n", cmd->infile);
        }
        if (cmd->outfile != NULL) {
            printf("Output file: %s\n", cmd->outfile);
        }

        // Print append mode
        printf("Append mode: %d\n", cmd->append);

        // Print file descriptors (if you need to)
        printf("File Descriptor (in): %d\n", cmd->fd_in);
        printf("File Descriptor (out): %d\n", cmd->fd_out);

        // Move to the next node in the list
        printf("\n"); // Add a newline for better readability between commands
        current = current->next;
    }
}


// int	main(int argc, char *argv[], char **env)
// {
// 	t_tokens	*l_tokens = NULL;
// 	char	**path = get_paths(env);

// 	if (argc != 2)
// 	{
// 		printf("Need 1 argument!\n");
// 		exit(0);
// 	}
// 	path = NULL;

// 	l_tokens = get_tokens(argv[1]);
// 	printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
// 	print_tokens(l_tokens);
// 	printf("~~~~~\n");

// 	t_list *lst_bag = get_bags_list(l_tokens);
// 	print_bag_contents(lst_bag);
// 	t_list_cmd *list_cmd = get_list_cmds_from_bags(lst_bag, path);
// 	print_list_cmds(list_cmd);
// 	list_cmd = NULL;
// 	free_tokens(l_tokens);
// 	// ft_lstclear(&lst_bag, fuck);
// 	return (0);
// }

	// printf("Command : %s\n", cmd_st.cmd);
	// t_list_arg *current_arg = cmd_st.args; // Use a temporary pointer for iteration
	// while (current_arg) {
	// 	printf("arguments : %s\n", current_arg->arg); // Print the current argument
	// 	current_arg = current_arg->next; // Move to the next argument
	// }
	// // printf("argument : %s\n", cmd_st.args[0]);
	// printf("Append mode: %d\n", cmd_st.append);
	// printf("infile name: %s\n",cmd_st.infile);
	// printf("outfile name: %s\n",cmd_st.outfile);