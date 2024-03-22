#include "../inc/minishell.h"

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		(*str) = NULL;
	}
}

void	clean_list_bag(t_list *list_bag)
{
	t_list	*tmp;

	tmp = NULL;
	if (!list_bag)
		return ;
	while (list_bag)
	{
		free(list_bag->content);
		tmp = list_bag->next;
		free (list_bag);
		list_bag = tmp;
	}
}

void	clean_list_arg(t_list_arg *args)
{
	t_list_arg	*tmp;

	tmp = NULL;
	if (!args)
		return ;
	while (args)
	{
		free(args->arg);
		tmp = args->next;
		free (args);
		args = tmp;
	}
}

void	clean_cmd_str(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->a_arg && cmd->a_arg[i])
	{
		free(cmd->a_arg[i]);
		i++;
	}
	if (cmd->a_arg)
	{
		free(cmd->a_arg);
		cmd->a_arg = NULL;
	}
	clean_list_arg(cmd->args);
	free_str(&cmd->heredoc);
	free_str(&cmd->infile);
	free_str(&cmd->outfile);
}

void	clean_list_cmd(t_list_cmd *list_cmd)
{
	t_list_cmd	*tmp;

	tmp = NULL;
	if (!list_cmd)
		return ;
	while (list_cmd)
	{
		clean_cmd_str(list_cmd->cmd);
		tmp = list_cmd->next;
		free(list_cmd);
		list_cmd = tmp;
	}
}
