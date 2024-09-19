/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:13 by albestae          #+#    #+#             */
/*   Updated: 2024/09/19 03:52:18 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <string.h>

static void	init_input(t_data *data, char **argv)
{
	if (ft_atoi(argv[1]) < 5)
		data->buffer.size = 32;
	else if (ft_atoi(argv[1]) > 10)
		data->buffer.size = 64;
 	else if (ft_atoi(argv[1]) > 50)
		data->buffer.size = 256;
	else
		data->buffer.size = 1024;
	data->buffer.str = malloc(sizeof(char) * data->buffer.size);
	if (!data->buffer.str)
		return ;
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
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal = data->start_time;
		data->philos[i].start_time = data->start_time;
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
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		data->philos[i].r_fork = &data->philos[(i + 1) % data->num_of_philos].l_fork;
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	init_meal_mutex(data);
	return (0);
}
void 	exit_properly(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	data.buffer.size = 16;
	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (write(2, "Invalid number of argument\n", 28), 1);
	if (ft_parsing(argv))
		return (1);
	if (init_data(&data, argv))
		return (1);
	create_threads(&data);
	print_buffer(&data.buffer, 1);
	exit_properly(&data);
	free(data.buffer.str);
	return (0);
}

void 	exit_properly(t_data *data)
{
	int i;

	i = 0;
	print_buffer(&data->buffer, 1);
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->philos);
	exit(0);
}