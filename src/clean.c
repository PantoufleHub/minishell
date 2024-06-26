/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:42 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:42 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_list_bag(t_list *list_bag)
{
	t_list	*tmp;
	t_list	*token_list;
	t_list	*tmp_token_list;
	char	*token;

	tmp = NULL;
	if (!list_bag)
		return ;
	while (list_bag)
	{
		token_list = (t_list *)(list_bag->content);
		while (token_list)
		{
			token = (char *)token_list->content;
			free(token);
			token = NULL;
			tmp_token_list = token_list;
			token_list = token_list->next;
			free(tmp_token_list);
			tmp_token_list = NULL;
		}
		tmp = list_bag->next;
		free (list_bag);
		list_bag = tmp;
	}
}

void	clean_list_arg(t_list_arg *args)
{
	t_list_arg	*tmp;

	tmp = NULL;
	if (!args)
		return ;
	while (args)
	{
		free(args->arg);
		args->arg = NULL;
		tmp = args->next;
		free (args);
		args = tmp;
	}
}

void	clean_cmd_str(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->a_arg && cmd->a_arg[i])
	{
		free(cmd->a_arg[i]);
		cmd->a_arg[i] = NULL;
		i++;
	}
	if (cmd->a_arg)
	{
		free(cmd->a_arg);
		cmd->a_arg = NULL;
	}
	free_str(&cmd->cmd);
	clean_list_arg(cmd->args);
	free_str(&cmd->heredoc);
	free_str(&cmd->infile);
	free_str(&cmd->outfile);
}

void	clean_list_cmd(t_list_cmd *list_cmd)
{
	t_list_cmd	*tmp;

	tmp = NULL;
	if (!list_cmd)
		return ;
	while (list_cmd)
	{
		clean_cmd_str(list_cmd->cmd);
		free(list_cmd->cmd);
		tmp = list_cmd->next;
		free(list_cmd);
		list_cmd = tmp;
	}
}

void	clean_swag(t_list_cmd *list_cmd, t_list *list_bag,
	char **paths, t_tokens *tokens)
{
	free_arr_str(paths);
	clean_list_bag(list_bag);
	clean_list_cmd(list_cmd);
	clean_tokens(tokens);
}
