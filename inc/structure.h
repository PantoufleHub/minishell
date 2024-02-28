#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_dim {
	size_t	x;
	size_t	y;
}	t_dim;

typedef struct s_cmd {
	char	**split;
	char	*cmd;
	char	**arg;
}	t_cmd;

typedef struct s_data {
	char	**path;
	char	*trim;
	int		n_cmd;
	t_cmd	*cmd;
}	t_data;

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

typedef struct s_parse
{
	int			index;
	int			in_quote;
}	t_parse;

#endif //STRUCTURE_H