/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:19 by albestae          #+#    #+#             */
/*   Updated: 2024/09/10 01:19:46 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// static int check_death(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->dead_lock);
// 	if (philo->data->dead_flag == 0)
// 		return (1);
// 	pthread_mutex_unlock(&philo->data->dead_lock);
// 	return (0);
// }

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// if (check_death(philo) == 1)
		// 	return (NULL);
		eat(philo);
		// if (check_death(philo) == 1)
		// 	return (NULL);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	i;
	pthread_t dead_flag;
	
	i = 0;
	data->start_time = get_current_time();
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, &routine,
			&data->philos[i]);
		i++;
	}
	// i = 0;
	// while (i < data->num_of_philos)
	// {
	// 	pthread_join(data->philos[i].thread_id, NULL);
	// 	i++;
	// }
	// pthread_create(&dead_flag, NULL, &monitoring, data);
	// pthread_join(dead_flag, NULL);
}

void	exit_properly(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->fork_mutex);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	free(data->philos);
}

// void	*monitoring(void *arg)
// {
// 	int	i;
// 	t_data *data;

// 	data = (t_data *)arg;
// 	while (data->dead_flag == 0)
// 	{
// 		i = 0;
// 		while (i < data->num_of_philos)
// 		{
// 			pthread_mutex_lock(&data->philos[i].data->dead_lock);
// 			if (data->philos[i].is_alive == false)
// 			{
// 				pthread_mutex_unlock(&data->philos[i].data->dead_lock);
// 				exit_properly(data);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->philos[i].data->dead_lock);
// 			i++;
// 		}
// 	}
// 	return (NULL);
// }