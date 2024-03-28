/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bags_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:25 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:25 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	arg_helper(t_cmd *cmd_st)
{
	int			i;
	t_list_arg	*tmp;

	tmp = cmd_st->args;
	cmd_st->a_arg = malloc((args_size(cmd_st->args) + 2) * sizeof(char *));
	if (cmd_st->cmd)
		cmd_st->a_arg[0] = ft_strdup(cmd_st->cmd);
	else
		cmd_st->a_arg[0] = NULL;
	i = 1;
	while (tmp)
	{
		cmd_st->a_arg[i] = ft_strdup(tmp->arg);
		tmp = tmp->next;
		i++;
	}
	cmd_st->a_arg[i] = 0;
}

t_cmd	*bag_to_cmd(t_tokens *bag, char **path, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_cmd_st(cmd);
	fill_cmd_st(cmd, bag, path, shell);
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
		while ((tokens != NULL && (!(ft_strncmp(tokens->token, "|", 1) == 0)
					|| tokens->is_meta == 0)))
		{
			add_token(&current_tokens, tokens->token, tokens->is_meta);
			tokens = tokens->next;
		}
		current_bag = ft_lstnew(current_tokens);
		ft_lstadd_back(&bags, current_bag);
		if (tokens != NULL && ft_strncmp(tokens->token, "|", 1) == 0
			&& tokens->is_meta == 1)
			tokens = tokens->next;
	}
	return (bags);
}

t_list_cmd	*get_list_cmds_from_bags(t_list *bags, char **path, t_shell *shell)
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
		new_node->cmd = bag_to_cmd((t_tokens *)bags->content, path, shell);
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
