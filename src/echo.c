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
		return (0);
	if (!av[i])
	{
		printf("\n");
		return (0);
	}
	if ((ft_strncmp(av[i], "-n", 2) == 0)
		&& (ft_strncmp(av[i], "-n", ft_strlen(av[i])) == 0))
		echo_w_n(av);
	else
		echo_wo_n(av);
	return (0);
}
