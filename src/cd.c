#include "../inc/minishell.h"

int ft_cd_test(char **a_arg)
{
    char    *cwd;

    if (!a_arg[1])
        return (EXIT_FAILURE);
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return (EXIT_FAILURE);
    }
    printf("Current working directory: %s\n", cwd);
    if (chdir(a_arg[1]) == -1)
    {
        perror("chdir failed");
        return (EXIT_FAILURE);       
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return (EXIT_FAILURE);
    }
    printf("Current working directory: %s\n", cwd);   
    free(cwd);
    return (EXIT_SUCCESS);
}

int ft_cd(char **a_arg)
{
    if (!a_arg[1])
        return (EXIT_FAILURE);
    if (chdir(a_arg[1]) == -1)
    {
        perror("chdir failed\n");
        return (EXIT_FAILURE);       
    }
    return (EXIT_SUCCESS);
}

// int main(int ac,char **av)
// {
//     ft_cd_test(av);
//     ac = 0;
//     return (0);
// }
