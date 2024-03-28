/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:16 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:16 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		free (shell->env[i]);
		i++;
	}
	free (shell->env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell			swagshell;
	char			*line;
	char			*prompt;

	init_shell(&swagshell, envp);
	while (argv[0] && argc)
	{
		prompt = get_prompt();
		line = readline(prompt);
		interpret_line(line, &swagshell);
		if (line && line[0] != 0)
			add_history(line);
		free(line);
		free(prompt);
		set_signals();
	}
	clean_env(&swagshell);
	destroy_shell(&swagshell);
	return (0);
}
