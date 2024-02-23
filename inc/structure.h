#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_dim {
	size_t	x;
	size_t	y;
}	t_dim;

typedef struct s_cmd {
	char	*cmd;
	char	**arg;
}	t_cmd;

typedef struct s_data {
	char	**path;
	int		n_cmd;
	t_cmd	*cmd;
}	t_data;

#endif //STRUCTURE_H