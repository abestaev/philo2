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
        if (buff->i == BUFFER_SIZE)
            print_buffer(buff, 1);
        j++;
    }
}

void			write_char_buffer(t_buff *buff, char c)
{
    if (buff->i < BUFFER_SIZE - 1)
    {
        buff->str[buff->i] = c;
        buff->i++;
    }
    else
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
	pthread_mutex_lock(&philo->data->write_lock);

    write_longint_buffer(&philo->data->buffer, get_current_time() - philo->data->start_time);
    write_char_buffer(&philo->data->buffer, ' ');
    write_longint_buffer(&philo->data->buffer, philo->id + 1);
    write_char_buffer(&philo->data->buffer, ' ');
    write_str_buffer(&philo->data->buffer, msg);
    // ft_putnbr_fd((get_current_time() - philo->data->start_time), 1);
    // ft_putchar_fd(' ', 1);
    // ft_putnbr_fd(philo->id + 1, 1);
    // ft_putchar_fd(' ', 1);
    // ft_putstr_fd(msg, 1);
    // ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(&philo->data->write_lock);
}