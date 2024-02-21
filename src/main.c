/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:11:40 by aperron           #+#    #+#             */
/*   Updated: 2024/02/21 12:17:48 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void signal_handler(int signum)
{
	printf("\nRecieved signal: %d\n", signum);
	if (signum == 2)
	{
		exit(EXIT_SUCCESS);
	}
	if (signum == 3)
	{
		abort();
	}
}

int main(void)
{
	char *line;

	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		perror("Error registering signal handler");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("Command: ");

		if (!line)
		{
			printf("Terminating...\n");
			break ;
		}
		add_history(line);
		printf("Read line: %s\n", line);
		free(line);
	}
	return 0;
}
