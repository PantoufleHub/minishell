/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:33 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:33 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_shell_utils(t_shell *shell, char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	shell->env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env[i] = NULL;
}

void	init_shell(t_shell *shell, char **env)
{
	set_signals();
	set_terminal(&(shell->term_save));
	entry_display();
	shell->dollar_question_mark = 0;
	init_shell_utils(shell, env);
	shell->fd_in = dup(STDIN_FILENO);
	shell->fd_out = dup(STDOUT_FILENO);
	shell->heredocctrlc = 0;
	shell->heredoc_len = 0;
}

void	destroy_shell(t_shell *shell)
{
	restore_terminal(&(shell->term_save));
	exit(0);
}
