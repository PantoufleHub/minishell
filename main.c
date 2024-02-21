#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

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
