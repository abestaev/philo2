#include "../philo.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (1) // todo a update
	{
		printf("%ld %s %s\n", (get_current_time() - philo->data->start_time),
			philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}