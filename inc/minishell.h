#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <histedit.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>

# include "../libft/libft.h"
# include "structure.h"
# include "constants.h"

void					display_prompt(void);

void					exit_with_error(char *message);

void					error_message(char *message);

char					**get_paths(char *envp[]);

char 					*get_prompt();

void					interpret_line(char *line, char *envp[]);

void					set_signals(void);

void					set_signals_child(void);

void					signal_handler(int signum);

#endif