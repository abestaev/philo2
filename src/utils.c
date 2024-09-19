#include "../philo.h"

void				print_buffer(t_buff *buff, int fd)
{
    write(fd, buff->str, buff->i);
    buff->i = 0;
}

void			write_str_buffer(t_buff *buff, const char *str)
{
    int j;

    j = 0;
    while (str[j])
    {
        buff->str[buff->i] = str[j];
        buff->i++;
        j++;
        if (buff->i == buff->size)
            print_buffer(buff, 1);
    }
}

void			write_char_buffer(t_buff *buff, char c)
{
    buff->str[buff->i] = c;
    buff->i++;
    if (buff->i == buff->size)
        print_buffer(buff, 1);
}

void			write_longint_buffer(t_buff *buff, long int nb)
{
    if (nb < 0)
    {
        write_char_buffer(buff, '-');
        nb *= -1;
    }
    if (nb >= 10)
        write_longint_buffer(buff, nb / 10);
    write_char_buffer(buff, (nb % 10) + '0');
}

void	print_message(t_philo *philo, char *msg)
{
    int ret;

    ret = 0;
    pthread_mutex_lock(&philo->data->dead_lock);
    ret = philo->data->dead_flag;
    pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->write_lock);
    if (ret)
    {
        pthread_mutex_unlock(&philo->data->write_lock);
        return ;
    }
    write_longint_buffer(&philo->data->buffer, get_current_time() - philo->start_time);
    write_char_buffer(&philo->data->buffer, ' ');
    write_longint_buffer(&philo->data->buffer, philo->id + 1);
    write_char_buffer(&philo->data->buffer, ' ');
    write_str_buffer(&philo->data->buffer, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_death(t_philo *philo, char *msg)
{
    int ret;

    ret = 0;
	pthread_mutex_lock(&philo->data->write_lock);
    // pthread_mutex_lock(&philo->data->dead_lock);
    // ret = philo->data->dead_flag;
    // pread_mutex_unlock(&philo->data->dead_lock);
    if (ret)
    {
        pthread_mutex_unlock(&philo->data->write_lock);
        return ;
    }
    write_longint_buffer(&philo->data->buffer, get_current_time() - philo->start_time);
    write_char_buffer(&philo->data->buffer, ' ');
    write_longint_buffer(&philo->data->buffer, philo->id + 1);
    write_char_buffer(&philo->data->buffer, ' ');
    write_str_buffer(&philo->data->buffer, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}