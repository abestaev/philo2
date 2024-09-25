/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:19 by albestae          #+#    #+#             */
/*   Updated: 2024/09/25 23:41:05 by albestae         ###   ########.fr       */
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
		if (philo->data->num_of_philos == 1)
			usleep(100);
		else
		{
			if (philo->meals_eaten != philo->data->meals_to_eat)
				eat(philo);
			if (philo->meals_eaten != philo->data->meals_to_eat)
				sleep_and_think(philo);
		}
	}
	return (NULL);
}

static void	launch_philo(t_data *data)
{
	int	i;

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
	launch_philo(data);
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
	int		i;
	size_t	time;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->num_of_philos)
		{
			time = get_meal_time(&data->philos[i]);
			if ((time) > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_lock);
				print_death(&data->philos[i], "died\n");
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
		}
		if (check_meals(data))
			return (NULL);
		usleep(120);
	}
	return (NULL);
}
