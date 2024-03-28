/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:40 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:40 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->token)
		{
			free(tokens->token);
			tokens->token = NULL;
		}
		if (tokens)
		{
			free(tokens);
			tokens = NULL;
		}
		tokens = tmp;
	}
}

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		(*str) = NULL;
	}
}
