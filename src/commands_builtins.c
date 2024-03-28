/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:56 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:56 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redup(t_cmd *cmd, t_shell *shell)
{
	if (cmd->outfile && cmd->fd_out != STDOUT_FILENO)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		close(shell->fd_out);
	}
	if (cmd->infile && cmd->fd_in != STDIN_FILENO)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		close(shell->fd_in);
	}
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		ret = (ft_cd(cmd->a_arg, shell));
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		ret = (ft_exit(EXIT_SUCCESS));
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		ret = (ft_echo(cmd->a_arg));
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ret = (ft_pwd());
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		ret = (ft_export(cmd->a_arg, shell));
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ret = (ft_env(shell));
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		ret = (ft_unset(shell, cmd->a_arg));
	redup(cmd, shell);
	return (ret);
}
