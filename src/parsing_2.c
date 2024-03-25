#include "../inc/minishell.h"

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

int	end_of_line(int in_quote, t_string *token, t_tokens **tokens)
{
	char *prout;

	if (in_quote)
	{
		ft_printf("Unfinished quotes!\n");
		return (0);
	}
	if (token)
	{
		prout = get_string(token);
		add_token(tokens, prout);
		free(prout);
		free_string(token);
	}
	token = NULL;
	return (1);
}

void	acco_tokenizor(t_string **token, t_tokens **tokens, char *line,
	t_parse *p)
{
	char *prout;

	if (*token)
	{
		prout = get_string(*token);
		add_token(tokens, prout);
		free(prout);
		free_string(*token);
	}
	*token = NULL;
	add_char(token, line[p->index]);
	add_char(token, line[p->index + 1]);
	prout = get_string(*token);
	add_token(tokens, prout);
	free(prout);
	free_string(*token);
	*token = NULL;
	p->index++;
}

void	pipo_tokenizor(t_string **token, t_tokens **tokens, char *line,
	t_parse *p)
{
	char *prout;

	if (*token)
	{
		prout = get_string(*token);
		add_token(tokens, prout);
		free(prout);
		free_string(*token);
	}
	*token = NULL;
	add_char(token, line[p->index]);
	prout = get_string(*token);
	add_token(tokens, prout);
	free(prout);
	free_string(*token);
	*token = NULL;
}
