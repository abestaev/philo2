#include "philo.h"

// static void ft_atoi(char *str)
// {

// }

static int  ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
//todo check if size > max int
static int ft_onlydigit(char *str)
{
    int i;

    i = 0;
    if (str[i] < '0' || str[i] > '9')
        return (1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int ft_parsing(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc == 5 || argc == 6)
    {
        while (i < 5)
        {
            if (ft_onlydigit(argv[i]))
                return (1);
            i++;
        }
        if (argc == 6)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
            if (ft_onlydigit(argv[5]))
                return (1);
    }
    else
        return (1);
    return (0);
}