/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bags_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:23 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:23 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	chev_utils2(t_tokens **token)
{
	if (access((*token)->token, F_OK) == 0
		&& access((*token)->token, W_OK) == -1)
	{
		printf("Error accessing file\n");
		return (-1);
	}
	return (0);
}

int	chev_utils(t_cmd **cmd_st, t_tokens **token, int a)
{
	(*cmd_st)->append = a;
	*token = (*token)->next;
	if ((*cmd_st)->append == 0)
	{
		if (chev_utils2(token) == -1)
			return (-1);
		(*cmd_st)->fd_out = open((*token)->token,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if ((*cmd_st)->append == 1)
	{
		if (chev_utils2(token) == -1)
			return (-1);
		(*cmd_st)->fd_out = open((*token)->token, 0x209, 0644);
	}
	if ((*cmd_st)->outfile)
		free((*cmd_st)->outfile);
	(*cmd_st)->outfile = ft_strdup((*token)->token);
	return (1);
}

void	chev_utils_bis2(t_cmd **cmd_st, t_tokens **token, int a, t_shell *shell)
{
	*token = (*token)->next;
	(*cmd_st)->heredoc = heredoc(token, shell);
	(*cmd_st)->doc = a;
}

int	chev_utils_bis(t_cmd **cmd_st, t_tokens **token, int a, t_shell *shell)
{
	if (a == 1)
		chev_utils_bis2(cmd_st, token, a, shell);
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
