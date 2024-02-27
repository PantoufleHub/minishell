#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_string
{
	char			c;
	struct s_string	*next;
}	t_string;

void	print_tokens(t_tokens *l_tokens)
{
	while (l_tokens)
	{
		printf("|%s|\n", l_tokens->token);
		l_tokens = l_tokens->next;
	}
}

void	add_token(t_tokens **l_tokens, char *token)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	new->token = token;
	new->next = NULL;
	if (!(*l_tokens))
		*l_tokens = new;
	else
	{
		tmp = *l_tokens;
		while ((tmp)->next)
			(tmp) = (tmp)->next;
		(tmp)->next = new;
	}
}

int	string_len(t_string *string)
{
	int			len;

	len = 0;
	while (string)
	{
		string = string->next;
		len++;
	}
	return (len);
}

char	*get_string(t_string *string)
{
	int		len;
	char	*str;
	int		index;

	str = malloc(sizeof(char) * (string_len(string) + 1));
	index = 0;
	while (string)
	{
		str[index] = string->c;
		string = string->next;
		index++;
	}
	str[index] = 0;
	return (str);
}

void	add_char(t_string **string, char c)
{
	t_string	*new;
	t_string	*tmp;

	new = malloc(sizeof(t_string));
	new->c = c;
	new->next = NULL;
	if (!(*string))
		*string = new;
	else
	{
		tmp = *string;
		while ((tmp)->next)
			(tmp) = (tmp)->next;
		(tmp)->next = new;
	}
}

void	free_string(t_string *string)
{
	t_string	*tmp;

	tmp = string;
	while (string)
	{
		// free(string->c);
		tmp = string;
		free(string);
		string = tmp->next;
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
		free(tokens);
		tokens = tmp->next;
	}
}

void	parse(t_tokens **tokens, char *line)
{
	t_string	*token;
	int			index;
	int			in_quote;

	index = 0;
	in_quote = 0;
	while (1)
	{
		if (line[index] == 0)
		{
			if (in_quote)
			{
				printf("Unfinished quotes!\n");
				exit(0);
			}
			if(token)
			{
				add_token(tokens, get_string(token));
				free_string(token);
			}
			token = NULL;
			break ;
		}
		else if (!in_quote)
		{
			if (line[index] != ' ')
			{
				if (line[index] == '|' || line[index] == '<' || line[index] == '>')
				{
					if ((line[index] == '<' && line[index + 1] == '<') ||
						(line[index] == '>' && line[index + 1] == '>'))
					{
						if (token)
						{
							add_token(tokens, get_string(token));
							free_string(token);
						}
						token = NULL;
						add_char(&token, line[index]);
						add_char(&token, line[index + 1]);
						add_token(tokens, get_string(token));
						free_string(token);
						token = NULL;
						index++;
					}
					else
					{
						if (token)
							add_token(tokens, get_string(token));
						token = NULL;
						add_char(&token, line[index]);
						add_token(tokens, get_string(token));
						free_string(token);
						token = NULL;
					}
				}
				else
				{
					if (line[index] == '\'')
						in_quote = 1;
					if (line[index] == '"')
						in_quote = 2;
					add_char(&token, line[index]);
				}
			}
			else if (token)
			{
				add_token(tokens, get_string(token));
				free_string(token);
				token = NULL;
			}
		}
		else if (in_quote)
		{
			if ((in_quote == 1 && line[index] == '\'') || (in_quote == 2 && line[index] == '"'))
				in_quote = 0;
			add_char(&token, line[index]);
		}
		index++;
	}
}

t_tokens	*get_tokens(char *line)
{
	t_tokens	*l_tokens;

	l_tokens = NULL;
	parse(&l_tokens, line);
	return (l_tokens);
}

int	main(int argc, char *argv[])
{
	t_tokens	*l_tokens;

	if (argc != 2)
	{
		printf("Need 1 argument!\n");
		exit(0);
	}
	l_tokens = get_tokens(argv[1]);
	printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
	print_tokens(l_tokens);
	printf("~~~~~\n");
	free_tokens(l_tokens);
	return (0);
}
