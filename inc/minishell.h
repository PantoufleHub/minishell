#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>

# include "../libft/libft.h"
# include "structure.h"
# include "constants.h"

void					signal_handler(int signum);

void					set_signals(void);

void					display_prompt(void);

void					interpret_command(char *command);

#endif