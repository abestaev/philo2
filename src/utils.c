#include "../philo.h"

void    ft_putchar_fd(char c, int fd)
{
    if (fd >= 0)
        write(fd, &c, 1);
}

void    ft_putstr_fd(char *s, int fd)
{
    if (fd >= 0)
    {
        while (s && *s)
        {
            write(fd, &*s, 1);
            s++;
        }
    }
}

void    ft_putnbr_fd(long int ln, int fd)
{
    if (ln < 0)
    {
        ln *= -1;
        ft_putchar_fd('-', fd);
    }
    if (ln >= 10)
    {
        ft_putnbr_fd(ln / 10, fd);
        ft_putnbr_fd(ln % 10, fd);
    }
    else
    {
        if (fd >= 0)
            ft_putchar_fd(ln + '0', fd);
    }
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void	print_message(t_philo *philo, char *msg)
{
    if (philo->data->dead_flag)
        return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%ld %d %s\n", (get_current_time() - philo->data->start_time), philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}