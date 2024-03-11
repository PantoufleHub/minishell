#include "../inc/minishell.h"

int	n_count_echo(t_list_arg *args)
{
	int			i;
	t_list_arg	*tmp;

	tmp = args;
	i = 0;
	while (tmp)
	{
		if ((ft_strncmp(tmp->arg, "-n", 2) == 0)
			&& (ft_strncmp(tmp->arg, "-n", ft_strlen(tmp->arg)) == 0))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	echo_wo_n(t_list_arg *args)
{
	int			i;
	int			count;
	t_list_arg	*tmp;

	tmp = args;
	i = 0;
	count = 0;
	while (tmp)
	{
		if (count)
			printf(" ");
		count = printf("%s", tmp->arg);
		tmp = tmp->next;
	}
	printf("\n");
	return (0);
}

int	echo_w_n(t_list_arg *args)
{
	int			i;
	int			count;
	t_list_arg	*tmp;

	tmp = args;
	count = 0;
	i = n_count_echo(args);
	while (tmp)
	{
		while (i > 0)
		{
			tmp = tmp->next;
			i--;
		}
		if (count)
			printf(" ");
		count = printf("%s", tmp->arg);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_echo(t_list_arg *args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!args)
		return (0);
	if ((ft_strncmp(args->arg, "-n", 2) == 0)
		&& (ft_strncmp(args->arg, "-n", ft_strlen(args->arg)) == 0))
		echo_w_n(args);
	else
		echo_wo_n(args);
	return (0);
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
//         if (cmd->outfile != NULL) {
//             printf("Output file: %s\n", cmd->outfile);
//         }

//         // Print append mode
//         printf("Append mode: %d\n", cmd->append);
// 		if (cmd->heredoc)
// 			printf("Heredoc content :%s\n", cmd->heredoc);
//         // // Print file descriptors (if you need to)
//         // printf("File Descriptor (in): %d\n", cmd->fd_in);
//         // printf("File Descriptor (out): %d\n", cmd->fd_out);

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
// 	ft_echo(list_cmd->cmd->args);
// 	free_tokens(l_tokens);
// 	// ft_lstclear(&lst_bag, fuck);
// 	return (0);
// }
