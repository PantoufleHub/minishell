#include "../inc/minishell.h"

// int	ft_strncmp(const char *str1, const char *str2, size_t n)
// {
// 	size_t	index;

// 	index = 0;
// 	while (index < n)
// 	{
// 		if (str1[index] == '\0' || str1[index] != str2[index])
// 			return ((unsigned char)str1[index] - (unsigned char)str2[index]);
// 		index++;
// 	}
// 	return (0);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	l;

// 	l = 0;
// 	while (s[l] != '\0')
// 		l++;
// 	return (l);
// }

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
	if ((ft_strncmp(av[i], "-n", 2) == 0)
		&& (ft_strncmp(av[i], "-n", ft_strlen(av[i])) == 0))
		echo_w_n(av);
	else
		echo_wo_n(av);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		printf ("\n");
	else
		ft_echo(av);
	return (0);
}
