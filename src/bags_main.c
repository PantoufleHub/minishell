#include "../inc/minishell.h"

void	arg_helper(t_cmd *cmd_st)
{
	int		i;

	i = 1;
	if (!cmd_st->args || !cmd_st->cmd)
		return ;
	cmd_st->a_arg = malloc((args_size(cmd_st->args) + 2) * sizeof(char *));
	cmd_st->a_arg[0] = cmd_st->cmd;
	while (cmd_st->args)
	{
		cmd_st->a_arg[i] = cmd_st->args->arg;
		cmd_st->args = cmd_st->args->next;
		i++;
	}
	cmd_st->a_arg[i] = 0;
	cmd_st->args = NULL;
}

t_cmd	*bag_to_cmd(t_tokens *bag, char **path)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_cmd_st(cmd);
	fill_cmd_st(cmd, bag, path);
	arg_helper(cmd);
	return (cmd);
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
		while (tokens != NULL && !(ft_strncmp(tokens->token, "|", 1) == 0))
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

// t_tokens	*get_tokens(char *line)
// {
// 	t_tokens	*l_tokens;

// 	l_tokens = NULL;
// 	parse(&l_tokens, line);
// 	return (l_tokens);
// }

// void print_bag_contents(t_list *bags) {
//     while (bags) {
//         t_tokens *tokens_in_bag = (t_tokens *)(bags->content);

//         while (tokens_in_bag) {
//             printf("%s\n", tokens_in_bag->token);
//             tokens_in_bag = tokens_in_bag->next;
//         }
// 		printf("------\n");
//         bags = bags->next; // Move to the next bag
//     }
// }

// void print_list_cmds(t_list_cmd *list_cmd) {
//     t_list_cmd *current = list_cmd;

//     // Iterate over each node in the list
//     while (current != NULL) {
//         t_cmd *cmd = current->cmd;

//         // Print command type
//         printf("Command type: %d\n", cmd->cmd_type);

//         // Print command
//         if (cmd->cmd != NULL) {
//             printf("Command: %s\n", cmd->cmd);
//         }

//         // Print arguments
// 		t_list_arg *current_arg = cmd->args;
// 		printf("Arguments:");
// 		while (current_arg != NULL) {
// 			if (current_arg->arg != NULL) {
// 				printf(" %s", current_arg->arg);
// 			}
// 			current_arg = current_arg->next;
// 		}
//         printf("\n");

//         // Print infile and outfile
//         if (cmd->infile != NULL) {
//             printf("Input file: %s\n", cmd->infile);
//         }
// 		printf("Heredoc state: %d\n", cmd->doc);
//         if (cmd->outfile != NULL) {
//             printf("Output file: %s\n", cmd->outfile);
//         }

//         // Print append mode
//         printf("Append mode: %d\n", cmd->append);
// 		if (cmd->heredoc)
// 			printf("Heredoc content :%s\n", cmd->heredoc);
// 		printf("Error mode : %d\n", cmd->error);
// 		int a = 0;
// 		if (cmd->a_arg)
// 		{
// 			while (cmd->a_arg[a])
// 			{
// 				printf("content of the arg table n:%d, %s\n",a , cmd->a_arg[a]);
// 				a++;
// 			}
// 		}

//         // Move to the next node in the list
// 		printf("~~~~~~~~~~~~~~~~~~\n");
//         current = current->next;
//     }
// }

// int	main(int argc, char *argv[], char **env)
// {
// 	t_tokens	*l_tokens = NULL;
// 	char	**path = get_paths(env);

// 	if (argc != 2)
// 	{
// 		printf("Need 1 argument!\n");
// 		exit(0);
// 	}

// 	l_tokens = get_tokens(argv[1]);
// 	// printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
// 	// print_tokens(l_tokens);
// 	// printf("~~~~~\n");

// 	t_list *lst_bag = get_bags_list(l_tokens);
// 	// print_bag_contents(lst_bag);
// 	t_list_cmd *list_cmd = get_list_cmds_from_bags(lst_bag, path);
// 	print_list_cmds(list_cmd);
// 	free_tokens(l_tokens);
// 	// ft_lstclear(&lst_bag, fuck);
// 	return (0);
// }
