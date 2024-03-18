#include "../inc/minishell.h"

int	ft_export(char **export)
{
	int	i;

	i = 0;
	if (!export)
		return (0);
	while (export[i])
	{
		printf("%s\n", export[i]);
		i++;
	}
	return (0);
}

int	export_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (!((arg[0] >= 'A' && arg[0] <= 'Z') 
		|| (arg[0] >= 'a' && arg[0] <= 'z') || arg[0] == '_'))
	{
		printf("export : %s: not a valid identifier\n", arg);
		return (0);
	}
	while (arg[i])
	{
		if (!((arg[i] >= 'A' && arg[i] <= 'Z') 
			|| (arg[i] >= 'a' && arg[i] <= 'z') 
			|| (arg[i] >= '0' && arg[i] <= '9') 
			|| arg[i] == '_')) 	
		{
			printf("export : %c: not a valid identifier\n", arg[i]);
			return (0);	
		}
		i++;
	}
	return (1);
}

void	free_arr_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

char	**add_var(char **export, char *a_arg)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	if (!export_syntax(a_arg))
		return (NULL);
	while (export[i])
		i++;
	new = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (export[i])
	{
		new[i] = ft_strdup(export[i]);
		i++;
	}
	new[i] = ft_strdup(a_arg);
	i++;
	new[i] = NULL;
	free_arr_str(export);
	return (new);
}

int	main(int ac, char **av, char **env)
{
	ac = 0;
	t_shell shell;
	char	**tmp;
	int i = 0;

	shell.dollar_question_mark = 0;
	tmp = NULL;
	while (env[i])
		i++;
	shell.env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		shell.env[i] = ft_strdup(env[i]);
		i++;
	}
	shell.env[i] = NULL;
	i = 1;
	while (av[i])
	{
		tmp = add_var(shell.env, av[i]);
		if (tmp != NULL)
			shell.env = tmp;
		i++;
	}
	// char **export = ulti_fuse_export(env);
	if (!av[1])
		ft_export(shell.env);
	return (0);
}