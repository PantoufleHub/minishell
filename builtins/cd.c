#include "../inc/minishell.h"

// int ft_cd(char **av)
// {
//     char    *cwd;
//     char    *newd;

//     cwd = getcwd(NULL, 0);
//     if (!cwd)
//     {
//         perror("getcwd");
//         return (EXIT_FAILURE);
//     }
//     printf("Current working directory: %s\n", cwd);
//     newd = av[1];
//     if (chdir(newd) == -1)
//     {
//         perror("chdir failed");
//         return (EXIT_FAILURE);       
//     }
//     cwd = getcwd(NULL, 0);
//     if (!cwd)
//     {
//         perror("getcwd");
//         return (EXIT_FAILURE);
//     }
//     printf("Current working directory: %s\n", cwd);   
//     free(cwd);
//     return (EXIT_SUCCESS);
// }

int main(int ac, char **av)
{
    if (chdir(av[1]) == -1)
    {
        perror("chdir failed");
        return (EXIT_FAILURE);       
    }
    return (0);
}
