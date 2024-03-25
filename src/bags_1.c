#include "../inc/minishell.h"

int	args_size(t_list_arg *args)
{
	int			count;
	t_list_arg	*current;

	if (!args)
		return (0);
	count = 0;
	current = args;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	init_cmd_st(t_cmd *new_cmd)
{
	new_cmd->append = 0;
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->a_arg = NULL;
	new_cmd->cmd_type = 0;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->heredoc = NULL;
	new_cmd->doc = 0;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->error = 0;
}

void	add_cmd_and_type_utils(char *cmd,
	t_tokens *token, t_cmd *st_cmd, char **path)
{
	cmd = get_cmd(path, token->token);
	if (cmd)
		st_cmd->cmd = ft_strdup(cmd);
	else
		st_cmd->cmd = ft_strdup(token->token);
	free(cmd);
	cmd = NULL;
}

int	add_cmd_and_type(t_tokens *token, t_cmd *st_cmd, char **path)
{
	const char	*builtins[8] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", NULL};
	int			len;
	int			i;
	char		*cmd;

	i = 0;
	len = ft_strlen(token->token);
	cmd = NULL;
	while (builtins[i])
	{
		if (ft_strncmp(token->token, builtins[i], len) == 0
			&& ft_strncmp(token->token, builtins[i],
				ft_strlen(builtins[i])) == 0)
		{
			st_cmd->cmd_type = CMD_BUILTIN;
			st_cmd->cmd = ft_strdup(token->token);
			return (1);
		}
		i++;
	}
	add_cmd_and_type_utils(cmd, token, st_cmd, path);
	return (1);
}

void	add_arg(t_cmd *cmd_st, char *arg)
{
	t_list_arg	*new_arg;
	t_list_arg	*last;

	new_arg = malloc(sizeof(t_list_arg));
	last = NULL;
	if (!new_arg)
		return ;
	new_arg->arg = ft_strdup(arg);
	new_arg->next = NULL;
	if (cmd_st->args == NULL)
		cmd_st->args = new_arg;
	else
	{
		last = cmd_st->args;
		while (last->next != NULL)
			last = last->next;
		last->next = new_arg;
	}
}
