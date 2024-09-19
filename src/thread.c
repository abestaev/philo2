/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:19 by albestae          #+#    #+#             */
/*   Updated: 2024/09/19 03:58:31 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 0)
		ret = 1;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (ret);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_death(philo))
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int			i;
	pthread_t	dead_flag;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	i = 1;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, &routine,
			&data->philos[i]);
		i += 2;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, &routine,
			&data->philos[i]);
		i += 2;
	}
	pthread_create(&dead_flag, NULL, &monitoring, data);
	pthread_join(dead_flag, NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	*monitoring(void *arg)
{
	int i;
	size_t time;
	t_data *data;

	data = (t_data *)arg;
	while (1)
	{
		// pthread_mutex_lock(&data->dead_lock);
		// if (data->dead_flag)
		// {
		// 	pthread_mutex_unlock(&data->dead_lock);
		// 	break ;
		// }
		// pthread_mutex_unlock(&data->dead_lock);
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->meal_lock);
			time  = get_current_time() - data->philos[i].last_meal;
			pthread_mutex_unlock(&data->meal_lock);
			if ((time ) > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_lock);
				print_death(&data->philos[i], "died\n");
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
			i++;
		}
		usleep(240);
	}
	return (NULL);
}
