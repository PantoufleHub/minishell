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

void	add_cmd(t_cmds **cmds, t_cmd *st_cmd)
{
	t_cmds	*new;
	t_cmds	*current;

	new = malloc(sizeof(t_cmds));
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

void	add_cmd_type(t_cmd *st_cmd, char *cmd)
{
	const char	*builtins[8] = {"echo", "cd", "pwd"
		,"export", "unset", "env", "exit", NULL};
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(cmd);
	st_cmd->cmd_type = CMD_EXTERNAL;
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], len) == 0
			|| ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
		st_cmd->cmd_type = CMD_BUILTIN;
		i++;
	}
}

/* int	baggin(t_tokens *token)
{
	char	**bag;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	bag == malloc((token_count(token) + 1) * sizeof(t_tokens));
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		if (ft_strncmp(token->token, "|", 1))
		{
			break ;
		}
		bag[i] = ft_strdup(token->token);
		token = token->next;
		i++;
	}
} */

//completement broken