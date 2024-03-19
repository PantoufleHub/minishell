#include "../inc/minishell.h"

int	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return (0);
	while (shell->env[i])
	{
		// printf("%s=%s\n", shell->vars[i]->key, shell->vars[i]->value);
		printf("%s\n", shell->env[i]);
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
				|| arg[i] == '_' || arg[i] == '='))
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

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count ++;
	return (count);
}

int	find_var_index(char *key, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == key[j] && key[j] != '=' && key[j])
		{
			if ((env[i][j + 1] == '=' || env[i][j + 1] == '\0')
				&& (key[j + 1] == '=' || key[j + 1] == '\0'))
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	var_utils(char **env, char *a_arg, char **new, int env_len)
{
	int	found;
	int	index;
	int	i;

	found = 0;
	index = 0;
	i = 0;
	index = find_var_index(a_arg, env);
	while (i < env_len)
	{
		if (index != -1 && i == index)
		{
			if (ft_strchr(a_arg, '=') != NULL)
			{
				new[i] = ft_strdup(a_arg);
				found = 1;
			}
			else
				new[i] = ft_strdup(env[i]);
		}
		else
			new[i] = ft_strdup(env[i]);
		i++;
	}
	if (!found && (ft_strchr(a_arg, '=') != NULL || index == -1))
		new[i++] = ft_strdup(a_arg);
	new[i] = NULL;
}

char	**add_var(char **export, char *a_arg)
{
	char	**new;
	int		env_len;

	new = NULL;
	if (!export_syntax(a_arg))
		return (NULL);
	env_len = count_env_vars(export);
	new = malloc((env_len + 2) * sizeof(char *));
	var_utils(export, a_arg, new, env_len);
	free_arr_str(export);
	return (new);
}

void	ft_export(char **a_arg, t_shell *shell)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = NULL;
	while (a_arg[i])
	{
		tmp = add_var(shell->env, a_arg[i]);
		if (tmp)
			shell->env = tmp;
		i++;
	}
	// printf("%s", shell->vars[1]->key);
	if (!a_arg[1])
		print_export(shell);
}

// int	main(int ac, char **av, char **env)
// {
// 	ac = 0;
// 	t_shell shell;
// 	char	**tmp;
// 	int i = 0;

// 	shell.dollar_question_mark = 0;
// 	tmp = NULL;
// 	while (env[i])
// 		i++;
// 	shell.env = malloc((i + 1) * sizeof(char *));
// 	i = 0;
// 	while (env[i])
// 	{
// 		shell.env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	shell.env[i] = NULL;
// 	i = 1;
// 	while (av[i])
// 	{
// 		tmp = add_var(shell.env, av[i]);
// 		if (tmp != NULL)
// 			shell.env = tmp;
// 		i++;
// 	}
// 	// char **export = ulti_fuse_export(env);
// 	if (!av[1])
// 		print_export(shell.env);
// 	return (0);
// }