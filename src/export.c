/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:09 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:09 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	var_utils_helper(char *a_arg, char **new, int *found, int i)
{
	new[i] = ft_strdup(a_arg);
	*found = 1;
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
				var_utils_helper(a_arg, new, &found, i);
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

char	**add_var_env(char **export, char *a_arg)
{
	char	**new;
	char	*key;
	int		env_len;

	new = NULL;
	key = copy_until_char_or_all(a_arg, '=');
	if (!export_syntax(key))
	{
		free(key);
		return (NULL);
	}
	free(key);
	env_len = count_env_vars(export);
	new = malloc((env_len + 2) * sizeof(char *));
	var_utils(export, a_arg, new, env_len);
	free_arr_str(export);
	return (new);
}

int	ft_export(char **a_arg, t_shell *shell)
{
	char	**tmp;
	int		i;
	int		ret;

	i = 1;
	ret = EXIT_SUCCESS;
	tmp = NULL;
	while (a_arg[i])
	{
		tmp = add_var_env(shell->env, a_arg[i]);
		if (tmp)
			shell->env = tmp;
		if (!tmp)
			ret = EXIT_FAILURE;
		i++;
	}
	if (!a_arg[1])
		print_export(shell);
	return (ret);
}
