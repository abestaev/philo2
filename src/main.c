/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:56:13 by albestae          #+#    #+#             */
/*   Updated: 2024/09/10 01:20:31 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

static int	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	init_input(data, argv);
	data->start_time = get_current_time();
	data->dead_flag = 0;
	data->philos = (t_philo *)malloc(data->num_of_philos * sizeof(t_philo));
	if (!data->philos)
		return (1);
	pthread_mutex_init(&data->fork_mutex, NULL);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		pthread_mutex_lock(&data->fork_mutex);
        data->philos[i].r_fork = &data->philos[(i + 1) % data->num_of_philos].l_fork;
        pthread_mutex_unlock(&data->fork_mutex);
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_current_time();
		// data->philos[i].is_alive = true;
		data->philos[i].data = data;
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid number of argument\n", 28), 1);
	if (ft_parsing(argv))
		return (1);
	if (init_data(&data, argv))
		return (1);
	create_threads(&data);
	loop(&data);
	//exit_properly(&data);
	return (0);
}

void loop(t_data *data)
{
	int i;	

	i = 0;
	while (data->dead_flag == 0)
	{
		pthread_mutex_lock(&data->meal_lock);
		if ((int )(get_current_time() - data->philos[i].last_meal) > data->time_to_die)
		{
			pthread_mutex_lock(&data->philos[i].data->dead_lock);
			data->dead_flag = 1;
			print_message(&data->philos[i], "died");
			pthread_mutex_unlock(&data->philos[i].data->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&data->meal_lock);
		i = (i + 1) % data->num_of_philos;
	}
};
