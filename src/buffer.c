/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:49:41 by albestae          #+#    #+#             */
/*   Updated: 2024/09/17 12:58:32 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void				print_buffer(t_buff *buff, int fd)
{
    write(fd, buff->str, buff->i);
    buff->i = 0;
}
void			write_str_buffer(t_buff *buff, const char *str, int size);
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
void			write_longint_buffer(t_buff *buff, long int nb);