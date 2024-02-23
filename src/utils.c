#include "../inc/minishell.h"

void	entry_display(void)
{
	ft_printf(CYN"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ft_printf(CYN"|"NRM"                    MINISHELL                        "CYN"|\n");
	ft_printf(CYN"|"MAG"                                                     "CYN"|\n");
	ft_printf(CYN"|"MAG"     Welcome to the best minishell project ever!     "CYN"|\n");
	ft_printf(CYN"|"MAG"  This project is brought to you by jbido and apéro  "CYN"|\n");
	ft_printf(CYN"|"MAG"                                                     "CYN"|\n");
	ft_printf(CYN"|"MAG"                                                     "CYN"|\n");
	ft_printf(CYN"|"YEL"     Please be nice and don't try to break it "RED"<3     "CYN"|\n");
	ft_printf(CYN"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void	error_message(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	exit_with_error(char *message)
{
	error_message(message);
	exit(1);
}
