#include "../inc/minishell.h"

void	arg_helper(t_cmd *cmd_st)
{
	int		i;

	cmd_st->a_arg = malloc((args_size(cmd_st->args) + 2) * sizeof(char *));
	cmd_st->a_arg[0] = ft_strdup(cmd_st->cmd);
	i = 1;
	while (cmd_st->args)
	{
		cmd_st->a_arg[i] = ft_strdup(cmd_st->args->arg);
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
