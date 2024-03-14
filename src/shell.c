# include "../inc/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->cmds = NULL;
	shell->dollar_question_mark = 0;
	shell->env = env;
}
