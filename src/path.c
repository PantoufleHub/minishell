/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:26 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:26 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env(char **envp, char *var)
{
	int		index;
	char	*str;
	int		len;

	index = 0;
	str = malloc(ft_strlen(var) + 2);
	ft_strncpy(str, var, ft_strlen(var));
	str[ft_strlen(var)] = '=';
	str[ft_strlen(var)+1] = 0;
	len = ft_strlen(str);
	while (envp[index] && ft_strncmp(str, envp[index], len))
		index++;
	free(str);
	if (envp[index])
		return (ft_strdup(envp[index] + len));
	return (NULL);
}

char	**get_paths(char *envp[])
{
	char	**paths;
	char	*find_path;

	find_path = NULL;
	find_path = get_env(envp, "PATH");
	paths = ft_split(find_path, ':');
	free(find_path);
	if (!paths)
		error_message("Unable to find paths");
	return (paths);
}
