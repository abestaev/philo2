#include "../philo.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo philos[PHILO_MAX];
    pthread_mutex_t forks[PHILO_MAX];

    if (argc != 5 && argc != 6)
        return (write(2, "Invalid number of argument\n", 28), 1);
    if (ft_parsing(argv))
        return (1);
    init_data(&data, philos, forks, argv);
    return (0);
}