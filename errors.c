#include "cub.h"

/*If any misconfiguration of any kind is encountered in the file, 
the program must exit properly and return "Error\n" 
followed by an explicit error message of your choice.*/

void error(char *message, t_all *all)
{
    ft_putendl_fd("Error", 1);
    ft_putendl_fd(message, 1);
    exit_game(all, EXIT_FAILURE);
}