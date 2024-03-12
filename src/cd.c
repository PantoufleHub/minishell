#include "../inc/minishell.h"

int ft_cd(void)
{
    char    *cwd;

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

// int main()
// {
//     ft_cd();
//     return (0);
// }