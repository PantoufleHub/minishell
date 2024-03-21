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
		set_signals();
		prompt = get_prompt();
		line = readline(prompt);
		interpret_line(line, &swagshell);
		add_history(line);
		free(line);
		free(prompt);
	}
	clean_env(&swagshell);
	destroy_shell(&swagshell);
	return (0);
}
