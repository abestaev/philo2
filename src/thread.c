/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:19 by albestae          #+#    #+#             */
/*   Updated: 2024/09/17 10:32:50 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int check_death(t_philo *philo)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 0)
		ret = 1;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (ret);
}

void	*even_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->dead_flag == 0)
	{
		eat(philo);
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
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	
	i = 1;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, &even_routine, &data->philos[i]);
		i += 2;
	}
	usleep(1000);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, &even_routine, &data->philos[i]);
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
	free(data->philos);
}

void	*monitoring(void *arg)
{
	int	i;
	size_t time;
	t_data *data;

	data = (t_data *)arg;
	while (data->dead_flag == 0)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->dead_lock);
			time = get_current_time();
			if ((time - data->philos[i].last_meal) > data->time_to_die)
			{
				data->dead_flag = 1;
				print_message(&data->philos[i], "died");
				pthread_mutex_unlock(&data->dead_lock);
				//exit_properly(data);
				break ;
			}
			pthread_mutex_unlock(&data->dead_lock);
			i++;
		}
	}
	return (NULL);
}