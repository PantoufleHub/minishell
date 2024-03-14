#include "../inc/minishell.h"

void    ft_env(char **env)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

// int main(int ac, char **av, char **env)
// {
//     ac = 0;
//     av = NULL;
//     ft_env(env);
//     return (0);
// }