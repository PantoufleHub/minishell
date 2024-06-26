/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:22 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:22 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	quotenizor(t_string **token, char *line, t_parse *p)
{
	if (line[p->index] == '\'')
	{
		p->in_quote = 1;
	}
	if (line[p->index] == '"')
	{
		p->in_quote = 2;
	}
	add_char(token, line[p->index]);
}

void	tokenizor(t_tokens **tokens, t_string **token)
{
	char	*prout;

	prout = get_string(*token);
	add_token(tokens, prout, 3);
	free(prout);
	prout = NULL;
	free_string(*token);
	*token = NULL;
}

void	in_quotenizor(t_string **token, char *line, t_parse *p)
{
	if ((p->in_quote == 1 && line[p->index] == '\'')
		|| (p->in_quote == 2 && line[p->index] == '"'))
	{
		p->in_quote = 0;
	}
	add_char(token, line[p->index]);
}

void	accopipo(t_string **token, t_tokens **tokens, char *line, t_parse *p)
{
	if ((line[p->index] == '<' && line[p->index + 1] == '<')
		|| (line[p->index] == '>' && line[p->index + 1] == '>'))
		acco_tokenizor(token, tokens, line, p);
	else
		pipo_tokenizor(token, tokens, line, p);
}
