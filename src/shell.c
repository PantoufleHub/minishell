# include "../inc/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	set_signals();
	set_terminal(&(shell->term_save));
	entry_display();
	shell->dollar_question_mark = 0;
	shell->single_cmd = 0;
	shell->env = env;
}

void	destroy_shell(t_shell *shell)
{
	restore_terminal(&(shell->term_save));
}
