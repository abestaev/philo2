/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:07:48 by albestae          #+#    #+#             */
/*   Updated: 2024/09/19 03:48:36 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
// # include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_buffer
{
	int					i;
	int				size;
	char				*str;
}						t_buff;	

typedef struct s_philo
{
	pthread_t			thread_id;
	size_t				start_time;
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	int					*dead_flag;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*dead_lock;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_of_philos;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_to_eat;
	size_t				start_time;
	int					dead_flag;
	t_buff				buffer;
	
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
}						t_data;

int						ft_parsing(char **argv);
int						ft_strlen(char *str);
int						ft_atoi(const char *str);
void					print_message(t_philo *philo, char *msg);
void					exit_properly(t_data *data);
size_t					get_current_time(void);
void					create_threads(t_data *data);
void					*routine(void *arg);
void					take_forks(t_philo *philo);
void					release_forks(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_and_think(t_philo *philo);
int						ft_usleep(size_t time);
void					*monitoring(void *arg);
void					loop(t_data *data);
int						check_death(t_philo *philo);

void					print_buffer(t_buff *buff, int fd);
void					write_str_buffer(t_buff *buff, const char *str);
void					write_char_buffer(t_buff *buff, char c);
void					write_longint_buffer(t_buff *buff, long int nb);


void	print_death(t_philo *philo, char *msg);	

#endif
