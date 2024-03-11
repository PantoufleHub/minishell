#include "../inc/minishell.h"

char	*heredoc(t_tokens **token)
{
	char	*line;
	char	*doc;

	doc = ft_strdup("");
	while (1)
	{
		line = readline("");
		if (!(ft_strncmp((*token)->token, line, ft_strlen((*token)->token)))
			&& !(ft_strncmp((*token)->token, line, ft_strlen(line))))
		{
			free (line);
			break ;
		}
		if (doc[0] != '\0')
			doc = ft_strjoin(doc, "\n");
		doc = ft_strjoin(doc, line);
		free(line);
	}
	return (doc);
}

int	store_chevron(t_cmd **cmd_st, t_tokens **token)
{
	if (ft_strncmp((*token)->token, "<<", 2) == 0)
	{
		*token = (*token)->next;
		(*cmd_st)->heredoc = heredoc(token);
		(*cmd_st)->doc = 1;
		return (1);
	}
	else if (ft_strncmp((*token)->token, "<", 1) == 0)
	{
		*token = (*token)->next;
		(*cmd_st)->infile = (*token)->token;
		(*cmd_st)->doc = 0;
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

void	fill_cmd_st(t_cmd *new_cmd, t_tokens *current_token, char **path)
{
	int	cmd_found;
	int	is_chevron;

	cmd_found = 0;
	is_chevron = 0;
	while (current_token)
	{
		is_chevron = store_chevron(&new_cmd, &current_token);
		if (cmd_found && !is_chevron)
		{
			add_arg(new_cmd, current_token->token);
		}
		if (!new_cmd->cmd && !is_chevron)
			cmd_found = add_cmd_and_type(current_token, new_cmd, path);
		current_token = current_token->next;
	}
}
