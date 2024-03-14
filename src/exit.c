#include "../inc/minishell.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	neg;
	int	value;

	index = 0;
	while (str[index] == '\n' || str[index] == '\r'
		|| str[index] == '\f' || str[index] == ' '
		|| str[index] == '\t' || str[index] == '\v')
		index++;
	neg = 1;
	if (str[index] == '-')
	{
		index++;
		neg = -1;
	}
	else if (str[index] == '+')
		index++;
	value = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		value = value * 10 + (str[index] - 48);
		index++;
	}
	return (value * neg);
}

void ft_exit(int status)
{
    exit(status);
}

// int main(int ac, char **av)
// {
//     ac = 0;
//     if (!av[1])
//         ft_exit(0);
//     ft_exit(ft_atoi(av[1]));
//     return (0);
// }
