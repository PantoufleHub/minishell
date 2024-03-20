#include "../inc/minishell.h"

void	redup(t_cmd *cmd, t_shell *shell)
{
	if (cmd->outfile && cmd->fd_out != STDOUT_FILENO)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		close(shell->fd_out);
	}
	if (cmd->infile && cmd->fd_in != STDIN_FILENO)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		close(shell->fd_in);
	}
}

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
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		ft_unset(shell, cmd->a_arg);
	redup(cmd, shell);
}
