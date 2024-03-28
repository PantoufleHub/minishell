/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:46 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:46 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reduce_env_utils(t_shell *shell, char **new, char *a_arg)
{
	int			i;
	int			j;
	int			index;
	const int	env_len = count_env_vars(shell->env);

	i = 0;
	j = 0;
	index = find_var_index(a_arg, shell->env);
	while (i < env_len)
	{
		if (index > -1 && index == i)
			i++;
		else
			new[j++] = ft_strdup(shell->env[i++]);
	}
	new[j] = NULL;
}

char	**reduce_env(t_shell *shell, char *a_arg)
{
	int		i;
	char	*key;
	char	**new;

	i = 0;
	key = copy_until_char_or_all(a_arg, '=');
	if (!export_syntax(key))
	{
		free(key);
		return (NULL);
	}
	free(key);
	i = count_env_vars(shell->env);
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	reduce_env_utils(shell, new, a_arg);
	free_arr_str(shell->env);
	return (new);
}

int	ft_unset(t_shell *shell, char **a_arg)
{
	int		i;
	int		ret;
	char	**tmp;

	i = 1;
	ret = EXIT_SUCCESS;
	tmp = NULL;
	while (a_arg[i])
	{
		tmp = reduce_env(shell, a_arg[i]);
		if (tmp)
			shell->env = tmp;
		if (!tmp)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
