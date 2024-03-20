#include "../inc/minishell.h"

void	close_paip(int *paips[], int cmd_nb)
{
	int	nb_paipos;

	if (!paips)
		return ;
	nb_paipos = 0;
	while (paips[nb_paipos])
		nb_paipos++;
	if (cmd_nb == 0)
		close(paips[cmd_nb][1]);
	else if (cmd_nb == nb_paipos)
		close(paips[cmd_nb - 1][0]);
	else
	{
		close(paips[cmd_nb - 1][0]);
		close(paips[cmd_nb][1]);
	}
}

void	choose_exec(t_cmd *cmd, int *paips[], int cmd_nb, t_shell *shell)
{
	set_signals_child();
	set_paip(cmd, paips, cmd_nb);
	close_paips(paips);
	set_in_out(cmd);
	if (cmd->cmd_type == CMD_BUILTIN)
		exec_builtin(cmd, shell);
	else
		exec_command(cmd, shell->env);
}

void	exec_commands(t_shell *shell, t_list_cmd *list_cmd)
{
	pid_t	pid;
	int		index;
	int		**paips;
	int		nb_cmd;

	index = 0;
	nb_cmd = count_cmds(list_cmd);
	paips = init_paips(nb_cmd - 1);
	while (list_cmd)
	{
		if (nb_cmd == 1 && list_cmd->cmd->cmd_type == CMD_BUILTIN)
			choose_exec(list_cmd->cmd, paips, index, shell);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				choose_exec(list_cmd->cmd, paips, index, shell);
				exit(0);
			}
		}
		list_cmd = list_cmd->next;
		index++;
	}
	close_paips(paips);
	while (wait(NULL) > 0)
		;
}
