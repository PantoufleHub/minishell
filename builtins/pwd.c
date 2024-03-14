#include "../inc/minishell.h"

int ft_pwd(char **a_arg)
{
    char    *cwd;

    a_arg = NULL;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd() error");
        return (EXIT_FAILURE);
    }
    printf("%s\n", cwd);
    free (cwd);
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    ac = 0;
    ft_pwd(av);
    return (0);
}