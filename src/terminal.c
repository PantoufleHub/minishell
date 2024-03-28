/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:07:44 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:44 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	restore_terminal(struct termios *save)
{
	tcsetattr(STDIN_FILENO, TCSANOW, save);
}

void	set_terminal(struct termios *save)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, save);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}
