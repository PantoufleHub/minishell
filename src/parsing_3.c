#include "../inc/minishell.h"

void	quotenizor(t_string **token, char *line, int *index, int *in_quote)
{
	if (line[*index] == '\'')
		*in_quote = 1;
	if (line[*index] == '"')
		*in_quote = 2;
	add_char(token, line[*index]);
}

void	tokenizor(t_tokens **tokens, t_string **token)
{
	add_token(tokens, get_string(*token));
	free_string(*token);
	*token = NULL;
}

void	in_quotenizor(t_string **token, char *line, int *in_quote, int index)
{
	if ((*in_quote == 1 && line[index] == '\'')
		|| (*in_quote == 2 && line[index] == '"'))
		*in_quote = 0;
	add_char(token, line[index]);
}

void	accopipo(t_string *token, t_tokens **tokens, char *line, int index)
{
	if ((line[index] == '<' && line[index + 1] == '<')
		|| (line[index] == '>' && line[index + 1] == '>'))
	{
		acco_tokenizor(token, tokens, line, &index);
	}
	else
		pipo_tokenizor(token, tokens, line, index);
}
