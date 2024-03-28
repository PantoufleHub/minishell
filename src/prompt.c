/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:28 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:28 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*cwd_np;
	size_t	lim;

	cwd = ft_calloc(4096, sizeof(char));
	getcwd(cwd, 4096);
	cwd_np = ft_strrchr(cwd, '/') + 1;
	lim = 20;
	if (ft_strlen(cwd_np) >= lim)
	{
		cwd_np[lim - 3] = '.';
		cwd_np[lim - 2] = '.';
		cwd_np[lim - 1] = '.';
		cwd_np[lim] = 0;
	}
	prompt = strings_join((char *[]){RED, "@Swag"YEL"Shell:"GRN, getenv("USER"),
			" "CYN, cwd_np, BLU"/: ", MAG, NULL});
	free(cwd);
	return (prompt);
}

void	display_prompt(void)
{
	char	*prompt;

	prompt = get_prompt();
	ft_printf(prompt);
	free(prompt);
}
