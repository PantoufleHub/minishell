#include "../inc/minishell.h"

void	close_paips(int **paips)
{
	int	index;

	index = 0;
	while (paips && paips[index])
	{
		close(paips[index][0]);
		close(paips[index][1]);
		index++;
	}
	index = 0;
	while (paips && paips[index])
	{
		free(paips[index]);
		index++;
	}
	free(paips);
}

int	**init_paips(int nb_paips)
{
	int	index;
	int	**paips;

	if (nb_paips <= 0)
		return (NULL);
	index = 0;
	paips = malloc((nb_paips + 1) * sizeof(int *));
	while (index < nb_paips)
	{
		paips[index] = malloc(2 * sizeof(int));
		pipe(paips[index]);
		index++;
	}
	paips[index] = NULL;
	return (paips);
}

void	set_paip(t_cmd *cmd, int *paips[], int cmd_nb)
{
	int	nb_paipos;

	if (!paips)
		return ;
	nb_paipos = 0;
	while (paips[nb_paipos])
		nb_paipos++;
	if (cmd_nb == 0)
	{
		if (!cmd->outfile)
			dup2(paips[cmd_nb][1], STDOUT_FILENO);
	}
	else if (cmd_nb == nb_paipos)
	{
		if (!cmd->infile)
			dup2(paips[cmd_nb - 1][0], STDIN_FILENO);
	}
	else
	{
		if (!cmd->infile)
			dup2(paips[cmd_nb - 1][0], STDIN_FILENO);
		if (!cmd->outfile)
			dup2(paips[cmd_nb][1], STDOUT_FILENO);
	}
}

void	set_in_out(t_cmd *cmd)
{
	int	pipo[2];

	if (cmd->doc)
	{
		pipe(pipo);
		write(pipo[1], cmd->heredoc, ft_strlen(cmd->heredoc));
		dup2(pipo[0], STDIN_FILENO);
		close(pipo[0]);
		close(pipo[1]);
	}
	else if (cmd->infile)
	{
		if (cmd->fd_in != STDIN_FILENO)
			dup2(cmd->fd_in, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

void	exec_command(t_cmd	*cmd, char **env)
{
	if (cmd->error)
		return ;
	if ((cmd->infile || cmd->heredoc) && !cmd->cmd)
	{
		exit(0);
	}
	if (!cmd->cmd)
		exit(0);
	if (cmd->fd_in && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out && cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (execve(cmd->cmd, cmd->a_arg, env) == -1)
	{
		printf("%s: command not found\n", cmd->cmd);
		exit(EXIT_FAILURE);
	}
	exit(0);
}
