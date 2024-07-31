#include "../philo.h"

static void    init_input(t_data *data, char **argv)
{
    data->num_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data->num_times_to_eat = ft_atoi(argv[5]);
    else
        data->num_times_to_eat = -1;
}
void    init_forks(pthread_mutex_t *forks, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void    init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal = get_current_time();
        philos[i].dead = &data->dead_flag;
        philos[i].l_fork = &forks[i];
        if (i == 0)
            philos[i].r_fork = &forks[data->num_of_philos - 1];
        else
            philos[i].r_fork = &forks[i - 1];
        i++;
    }
}

void    init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks, char **argv)
{
    init_input(data, argv);
    data->dead_flag = 0;
    data->philos = philos;
    pthread_mutex_init(&data->write_lock, NULL);
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);
    init_forks(forks, data->num_of_philos);
    init_philos(philos, data, forks);
}