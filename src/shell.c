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
	set_terminal(&(shell->term_save));
	entry_display();
	shell->dollar_question_mark = 0;
	init_shell_utils(shell, env);
}

void	destroy_shell(t_shell *shell)
{
	restore_terminal(&(shell->term_save));
	exit(0);
}
