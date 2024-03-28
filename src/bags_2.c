#include "../inc/minishell.h"

int	store_chevron(t_cmd **cmd_st, t_tokens **token, t_shell *shell)
{
	if (ft_strncmp((*token)->token, "<<", 2) == 0 && (*token)->is_meta)
	{
		return (chev_utils_bis(cmd_st, token, 1, shell));
	}
	else if (ft_strncmp((*token)->token, "<", 1) == 0 && (*token)->is_meta)
	{
		return (chev_utils_bis(cmd_st, token, 0, shell));
	}
	else if (ft_strncmp((*token)->token, ">>", 2) == 0 && (*token)->is_meta)
	{
		return (chev_utils(cmd_st, token, 1));
	}
	else if (ft_strncmp((*token)->token, ">", 1) == 0 && (*token)->is_meta)
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
