/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:48 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:54 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	patatipatata25lines(int *paips[], t_shell *shell)
{
	close_paips(paips);
	while (wait(&(shell->dollar_question_mark)) > 0)
		;
}

void	choose_exec(t_cmd *cmd, int *paips[], int cmd_nb, t_shell *shell)
{
	set_signals_child();
	set_paip(cmd, paips, cmd_nb);
	close_paips(paips);
	set_in_out(cmd);
	if (cmd->cmd_type == CMD_BUILTIN)
		shell->dollar_question_mark = exec_builtin(cmd, shell);
	else
		exec_command(cmd, shell->env);
}

void	exec_commands(t_shell *shell, t_list_cmd *list_cmd)
{
	pid_t	pid;
	int		index;
	int		**paips;
	int		nb_cmd;

	index = 0;
	nb_cmd = count_cmds(list_cmd);
	paips = init_paips(nb_cmd - 1);
	while (list_cmd)
	{
		if (nb_cmd == 1 && list_cmd->cmd->cmd_type == CMD_BUILTIN)
			choose_exec(list_cmd->cmd, paips, index, shell);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				choose_exec(list_cmd->cmd, paips, index, shell);
				exit(0);
			}
		}
		list_cmd = list_cmd->next;
		index++;
	}
	patatipatata25lines(paips, shell);
}
