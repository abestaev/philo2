/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:07:48 by albestae          #+#    #+#             */
/*   Updated: 2024/05/23 19:28:23 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define PHILO_MAX 200

typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t 			last_meal;

	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
    int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	size_t			start_time;	
    int				num_times_to_eat;
	int				dead_flag;
    
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

// parsing
int					ft_parsing(char **argv);
int ft_strlen(char *str);
int ft_atoi(const char *str);

// init
void    init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks, char **argv);

//action
void	print_message(t_philo *philo, char *msg);

//threads


//time
size_t get_current_time(void);

#endif
