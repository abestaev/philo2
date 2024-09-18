/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:13 by albestae          #+#    #+#             */
/*   Updated: 2024/09/18 22:44:55 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <string.h>

static void	init_input(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
}

static int	init_meal_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal = get_current_time();
		i++;
	}
	return (0);
}
static int	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	init_input(data, argv);
	data->start_time = get_current_time();
	data->dead_flag = 0;
	data->buffer.i = 0;
	data->philos = (t_philo *)malloc(data->num_of_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);
	pthread_mutex_init(&data->fork_mutex, NULL);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		pthread_mutex_lock(&data->fork_mutex);
		data->philos[i].r_fork = &data->philos[(i + 1)
			% data->num_of_philos].l_fork;
		pthread_mutex_unlock(&data->fork_mutex);
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	init_meal_mutex(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (write(2, "Invalid number of argument\n", 28), 1);
	if (ft_parsing(argv))
		return (1);
	if (init_data(&data, argv))
		return (1);
	create_threads(&data);
	// exit_properly(&data);
	return (0);
}
