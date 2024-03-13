#include "../inc/minishell.h"

void	set_in_out(t_cmd *cmd)
{
	if (cmd->infile)
	{
		// printf("Trying to open infile: \"%s\"...\n", cmd->infile);
		// int fd_in = open(cmd->infile, O_RDONLY);
		if (cmd->fd_in != STDIN_FILENO)
			dup2(cmd->fd_out, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		// printf("Trying to open outfile: \"%s\"...\n", cmd->outfile);
		// int fd_out = open(cmd->infile, O_WRONLY);
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

void	exec_command(t_cmd	*cmd, char **env)
{
	if (cmd->error)
		exit(0);
	set_in_out(cmd);
	if (cmd->cmd_type == CMD_EXTERNAL)
		execve(cmd->cmd, cmd->a_arg, env);
	else
		printf("Command %s not implemented yet!\n", cmd->cmd);
	exit(0);
}

void	wait_children(void)
{
	while (wait(NULL) > 0)
		;
}

void	exec_commands(t_list_cmd *list_cmd, char **env)
{
	pid_t	pid;
	int		index;

	index = 0;
	while (list_cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_command(list_cmd->cmd, env);
		list_cmd = list_cmd->next;
		index++;
	}
	wait_children();
}

//////////// FUNCTIONS BELOW ONLY FOR TESTING 

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
// 	// free_tokens(l_tokens);
// 	printf(RED "~~~~~~~ EXECUTION ~~~~~~~" NRM "\n");
// 	exec_commands(list_cmd, env);
// 	// ft_lstclear(&lst_bag, fuck);
// 	printf(RED SEP NRM);
// 	return (0);
// }
