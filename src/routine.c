/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:17 by albestae          #+#    #+#             */
/*   Updated: 2024/09/18 22:04:05 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork);
		print_message(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->l_fork);
		print_message(philo, "has taken a fork\n");
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_message(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	release_forks(philo);
}

void	sleep_and_think(t_philo *philo)
{
	print_message(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep);
	print_message(philo, "is thinking\n");
}