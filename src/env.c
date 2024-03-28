/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:03 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:03 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_shell *shell)
{
	int		i;
	char	*equal;

	i = 0;
	equal = NULL;
	if (!shell->env)
		return (EXIT_FAILURE);
	while (shell->env[i])
	{
		equal = ft_strchr(shell->env[i], '=');
		if (equal)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
