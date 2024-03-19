#include "../inc/minishell.h"

void	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		ft_cd(cmd->a_arg);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		ft_exit(EXIT_SUCCESS);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		ft_echo(cmd->a_arg);
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		ft_export(cmd->a_arg, shell);
	// else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
	// 	ft_env(env);
}
