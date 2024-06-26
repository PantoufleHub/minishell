/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jbidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:06:58 by jbidaux           #+#    #+#             */
/*   Updated: 2024/03/28 19:06:59 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	n_count_echo(char **av)
{
	int			i;
	int			count;

	i = 1;
	count = 0;
	while (av[i])
	{
		if ((ft_strncmp(av[i], "-n", 2) == 0)
			&& (ft_strncmp(av[i], "-n", ft_strlen(av[i])) == 0))
			count++;
		if ((ft_strncmp(av[i], "-n", 2) != 0)
			&& (ft_strncmp(av[i], "-n", ft_strlen(av[i])) != 0))
			break ;
		i++;
	}
	return (count);
}

int	echo_wo_n(char **av)
{
	int			i;

	i = 1;
	while (av[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", av[i]);
		i++;
	}
	printf("\n");
	return (0);
}

int	echo_w_n(char **av)
{
	int			n_count;
	int			i;

	n_count = n_count_echo(av);
	i = 1;
	if (!av[2])
		return (0);
	while (av[i])
	{
		while (n_count > 0)
		{
			n_count--;
			i++;
		}
		if (n_count < 0)
			printf(" ");
		if (n_count < 1)
		{
			printf("%s", av[i]);
			n_count--;
		}
		i++;
	}
	return (0);
}

int	ft_echo(char **av)
{
	int	i;

	i = 1;
	if (!av)
		return (EXIT_FAILURE);
	if (!av[i])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	if ((ft_strncmp(av[i], "-n", 2) == 0)
		&& (ft_strncmp(av[i], "-n", ft_strlen(av[i])) == 0))
		echo_w_n(av);
	else
		echo_wo_n(av);
	return (EXIT_SUCCESS);
}
