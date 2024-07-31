#include "../philo.h"

void    take_forks(t_philo *philo)
{
    if (philo->id % 2)
    {
        pthread_mutex_unlock(&philo->l_fork);
        print_message(philo, "has taken a fork");
        pthread_mutex_unlock(&philo->r_fork);
        print_message(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_unlock(&philo->r_fork);
        print_message(philo, "has taken a fork");
        pthread_mutex_unlock(&philo->l_fork);
        print_message(philo, "has taken a fork");
    }
}

void    release_forks(t_philo *philo)
{
    if (philo->id % 2)
    {
        pthread_mutex_unlock(&philo->l_fork);
        pthread_mutex_unlock(&philo->r_fork);
    }
    else
    {
        pthread_mutex_unlock(&philo->r_fork);
        pthread_mutex_unlock(&philo->l_fork);
    }
}

void    eat(t_philo *philo)
{

}

void sleep(t_philo *philo)
{

}

void think(t_philo *philo)
{

}