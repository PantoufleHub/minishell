#include "../inc/minishell.h"

char	*unquotor(char *token)
{
	int			index;
	int			in_quote;
	t_string	*new;
	char		*ret;

	index = 0;
	in_quote = 0;
	new = NULL;
	while (token[index])
	{
		quotexor(&in_quote, token[index]);
		if ((in_quote == 0 && token[index] != '\'' && token[index] != '"')
			|| (in_quote == 1 && token[index] != '\'')
			|| (in_quote == 2 && token[index] != '"'))
			add_char(&new, token[index]);
		index++;
	}
	ret = get_string(new);
	free_string(new);
	return (ret);
}

void	unquotokenator(t_tokens *tokens)
{
	char	*prout;

	while (tokens)
	{
		prout = tokens->token;
		tokens->token = unquotor(tokens->token);
		free(prout);
		tokens = tokens->next;
	}
}
