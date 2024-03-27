#include "../inc/minishell.h"

int	chev_utils(t_cmd **cmd_st, t_tokens **token, int a)
{
	(*cmd_st)->append = a;
	*token = (*token)->next;
	if ((*cmd_st)->append == 0)
	{
		if (access((*token)->token, F_OK) == 0
			&& access((*token)->token, W_OK) == -1)
		{
			printf("Error accessing file\n");
			return (-1);
		}
		(*cmd_st)->fd_out = open((*token)->token,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if ((*cmd_st)->append == 1)
	{
		if (access((*token)->token, F_OK) == 0
			&& access((*token)->token, W_OK) == -1)
		{
			printf("Error accessing file\n");
			return (-1);
		}
		(*cmd_st)->fd_out = open((*token)->token, 0x209, 0644);
	}
	if ((*cmd_st)->outfile)
		free((*cmd_st)->outfile);
	(*cmd_st)->outfile = ft_strdup((*token)->token);
	return (1);
}

int	 chev_utils_bis(t_cmd **cmd_st, t_tokens **token, int a, t_shell *shell)
{
	if (a == 1)
	{
		*token = (*token)->next;
		(*cmd_st)->heredoc = heredoc(token, shell);
		(*cmd_st)->doc = a;
	}
	if (a == 0)
	{
		*token = (*token)->next;
		if ((*cmd_st)->infile)
			free((*cmd_st)->infile);
		(*cmd_st)->infile = ft_strdup((*token)->token);
		if (access((*token)->token, F_OK) == -1)
		{
			printf("%s: No such file or directory\n", (*token)->token);
			return (-1);
		}
		if (open((*cmd_st)->infile, O_RDONLY) < 0)
		{
			printf("%s: Permission denied\n", (*cmd_st)->infile);
			return (-1);
		}
		(*cmd_st)->fd_in = open((*cmd_st)->infile, O_RDONLY);
		(*cmd_st)->doc = a;
	}
	return (1);
}

int	store_chevron(t_cmd **cmd_st, t_tokens **token, t_shell *shell)
{
	if (ft_strncmp((*token)->token, "<<", 2) == 0)
	{
		return (chev_utils_bis(cmd_st, token, 1, shell));
	}
	else if (ft_strncmp((*token)->token, "<", 1) == 0)
	{
		return (chev_utils_bis(cmd_st, token, 0, shell));
	}
	else if (ft_strncmp((*token)->token, ">>", 2) == 0)
	{
		return (chev_utils(cmd_st, token, 1));
	}
	else if (ft_strncmp((*token)->token, ">", 1) == 0)
	{
		return (chev_utils(cmd_st, token, 0));
	}
	return (0);
}

void	fill_cmd_st(t_cmd *new_cmd, t_tokens *current_token, char **path,
		t_shell *shell)
{
	int	cmd_found;
	int	is_chevron;

	cmd_found = 0;
	is_chevron = 0;
	while (current_token)
	{
		is_chevron = store_chevron(&new_cmd, &current_token, shell);
		if (is_chevron == -1)
		{
			new_cmd->error = 1;
			break ;
		}
		if (cmd_found && !is_chevron)
		{
			add_arg(new_cmd, current_token->token);
		}
		if (!new_cmd->cmd && !is_chevron)
			cmd_found = add_cmd_and_type(current_token, new_cmd, path);
		current_token = current_token->next;
	}
}
