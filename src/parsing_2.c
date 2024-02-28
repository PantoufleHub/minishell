#include "../inc/minishell.h"

void	free_string(t_string *string)
{
	t_string	*tmp;

	while (string)
	{
		tmp = string;
		string = string->next;
		free(tmp);
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tokens)
	{
		free(tokens->token);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
	}
}

void	end_of_line(int in_quote, t_string *token, t_tokens **tokens)
{
	if (in_quote)
	{
		ft_printf("Unfinished quotes!\n");
		exit(0);
	}
	if (token)
	{
		add_token(tokens, get_string(token));
		free_string(token);
	}
	token = NULL;
}

void	acco_tokenizor(t_string **token, t_tokens **tokens, char *line,
	t_parse *p)
{
	if (*token)
	{
		add_token(tokens, get_string(*token));
		free_string(*token);
	}
	*token = NULL;
	add_char(token, line[p->index]);
	add_char(token, line[p->index + 1]);
	add_token(tokens, get_string(*token));
	free_string(*token);
	*token = NULL;
	p->index++;
}

void	pipo_tokenizor(t_string **token, t_tokens **tokens, char *line,
	t_parse *p)
{
	if (*token)
	{
		add_token(tokens, get_string(*token));
		free_string(*token);
	}
	*token = NULL;
	add_char(token, line[p->index]);
	add_token(tokens, get_string(*token));
	free_string(*token);
	*token = NULL;
}
