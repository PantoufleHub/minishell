#include "../inc/minishell.h"

// count the token number in the list before processing it. Isn't used yet
int	token_count(t_tokens *token)
{
	int	count;

	count = 0;
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		count++;
		token = token->next;
	}
	count++;
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
void	add_cmd_and_type(t_tokens *token, t_cmd *st_cmd, char **path)
{
	const char	*builtins[8] = {"echo", "cd", "pwd"
		,"export", "unset", "env", "exit", NULL};
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(token->token);
	st_cmd->cmd_type = CMD_EXTERNAL;
	st_cmd->cmd = get_cmd(path, token->token);
	//censé set la commande dans la structure avec le chemin si la commande existe
	while (builtins[i])
	{
		if (ft_strncmp(token->token, builtins[i], len) == 0
			&& ft_strncmp(token->token, builtins[i], ft_strlen(builtins[i])) == 0)
		{
			st_cmd->cmd_type = CMD_BUILTIN;
			st_cmd->cmd = ft_strdup(token->token);
			//censé set la commande dans la structure comme tel car on doit la creer nous meme
		}
		i++;
	}
}

void	read_tokens(t_cmd **cmd_st, t_tokens **token, char **path)
{
	// if (!token)
	// 	return (NULL);
	while (*token)
	{
		if (ft_strncmp((*token)->token, "|", 1) == 0)
			break ;
		*cmd_st = malloc(sizeof(t_cmd));
		// if (ft_strncmp(token->token, "<", 1) == 0)
		// 	do smth
		// if (ft_strncmp(token->token, "<<", 2) == 0)
		// 	do smth
		// if (ft_strncmp(token->token, ">", 1) == 0)
		// 	do smth
		// if (ft_strncmp(token->token, ">>", 2) == 0)
		// 	do smth
		// if (ft_strncmp(token->token, "input_file", 69) == 0)
		// 	cmd_st->infile = ft_strdup(token->token);
		// if (ft_strncmp(token->token, "output_file", 69) == 0)
		// 	cmd_st->outfile = ft_strdup (token->token);
		// if (ft_strncmp(token->token, "cmd", 1) == 0)
		// 	do smth
		// if (ft_strncmp(token->token, "args", 1) == 0)
		// 	do smth
		add_cmd_and_type(*token, *cmd_st, path);
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

// int	main(int argc, char *argv[], char **env)
// {
// 	t_tokens	*l_tokens = NULL;
// 	char	**path = get_paths(env);
// 	t_cmd	*st_cmd = NULL;

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
// 	printf("%d\n",st_cmd->cmd_type);
// 	printf("%s\n",st_cmd->cmd);
// 	free_tokens(l_tokens);
// 	return (0);
// }