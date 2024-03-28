/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:42 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:42 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	last_chevron(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
		token = token->next;
	if ((ft_strncmp(token->token, ">", 1) == 0
			|| ft_strncmp(token->token, "<", 1) == 0
			|| ft_strncmp(token->token, ">>", 2) == 0
			|| ft_strncmp(token->token, "<<", 2) == 0)
		&& !token->next && token->is_meta == 1)
	{
		printf("parse error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	chevron_meta(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		if ((ft_strncmp(token->token, ">", 1) == 0
				|| ft_strncmp(token->token, "<", 1) == 0
				|| ft_strncmp(token->token, ">>", 2) == 0
				|| ft_strncmp(token->token, "<<", 2) == 0)
			&& (ft_strncmp(token->next->token, ">", 1) == 0
				|| ft_strncmp(token->next->token, "<", 1) == 0
				|| ft_strncmp(token->next->token, ">>", 2) == 0
				|| ft_strncmp(token->next->token, "<<", 2) == 0
				|| ft_strncmp(token->next->token, "|", 1) == 0)
			&& token->is_meta == 1)
		{
			printf("parse error\n");
			return (EXIT_FAILURE);
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

int	pipo_syntax(t_tokens *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->token, "|", 1) == 0)
	{
		broken_pipe();
		return (EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	if ((ft_strncmp(token->token, "|", 1) == 0)
		&& !token->next)
	{
		broken_pipe();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	dub_dub_chev(t_tokens *token)
{
	int	here_doc;

	here_doc = 0;
	if (!token)
		return (EXIT_SUCCESS);
	while (token->next)
	{
		if (ft_strncmp(token->token, "<<", 2) == 0)
			here_doc++;
		token = token->next;
	}
	if (here_doc >= 2)
	{
		printf("whatchya thinkin here, doc?\nbtw, go play Last Epoch\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	syntax_check(t_tokens *token)
{
	if (last_chevron(token) == 1)
		return (EXIT_FAILURE);
	if (pipo_syntax(token) == 1)
		return (EXIT_FAILURE);
	if (chevron_meta(token) == 1)
		return (EXIT_FAILURE);
	if (dub_dub_chev(token) == 1)
		return (EXIT_FAILURE);
	if (dub_pipo(token) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
