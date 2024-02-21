/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:11:40 by aperron           #+#    #+#             */
/*   Updated: 2024/02/21 14:52:18 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*prompt;
	char	*line;
	int		is_running;

	set_signals();
	is_running = 1;
	while (is_running)
	{
		prompt = get_prompt();
		line = readline(prompt);
		if (!line)
			is_running = 0;
		else
			interpret_command(line);
		add_history(line);
		free(prompt);
		free(line);
	}
	return (0);
}
