/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 04:10:11 by albestae          #+#    #+#             */
/*   Updated: 2024/09/25 23:40:59 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(100);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	get_meal_time(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->meal_lock);
	time = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (time);
}

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_to_eat == -1)
		return (0);
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten >= data->meals_to_eat)
		{
			data->meals_done++;
			if (data->meals_done == data->num_of_philos)
			{
				pthread_mutex_lock(&data->dead_lock);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->dead_lock);
				print_message(&data->philos[i], "\n");
				pthread_mutex_unlock(&data->meal_lock);
				return (1);
			}
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (0);
}
