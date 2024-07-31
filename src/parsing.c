#include "../philo.h"

int ft_atoi(const char *str)
{
    int i;
    long num;

    num = 0;
    i = 0;
    while (str[i])
    {
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    return (num); 
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int ft_maxint(char *str)
{
    if (ft_strlen(str) > 10)
        return (1);
    if (ft_strlen(str) == 10)
        if (ft_strcmp(str, "2147483647") > 0)
            return (1);
    return (0);
}

static int ft_valid_arg(char *str)
{
    int i;

    i = 0;
    if (ft_maxint(str))
        return (1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int ft_parsing(char **argv)
{
    if (ft_valid_arg(argv[1]) || ft_atoi(argv[1]) > 200)
        return (write(2, "Invalid philosophers number\n", 29), 1);
    if (ft_valid_arg(argv[2]))
        return (write(2, "Invalid time to die\n", 21));
    if (ft_valid_arg(argv[3]))
        return (write(2, "Invalid time to eat\n", 21));
    if (ft_valid_arg(argv[4]))
        return (write(2, "Invalid time to sleep\n",23));
    if (argv[5] && ft_valid_arg(argv[5]))
        return (write(2, "Invalid number of time each philosopher must eat\n", 51));
    return (0);
}