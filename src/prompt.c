/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperron <aperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:32:06 by aperron           #+#    #+#             */
/*   Updated: 2024/02/21 14:50:48 by aperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*name;
	char	*pwd;
	char	*home;

	name = getenv("USER");
	pwd = getenv("PWD");
	home = getenv("HOME");
	prompt = ft_strjoin(name, ": ");
	return (prompt);
}
