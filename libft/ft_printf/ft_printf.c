/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:42:22 by kerlee            #+#    #+#             */
/*   Updated: 2026/03/18 09:41:53 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	process_format(const char **format, t_data *data)
{
	char	*initial_format;

	initial_format = (char *)*format;
	while (is_flag(**format, data) == true)
		(*format)++;
	data->width = add_number(format);
	if (**format == '.')
	{
		data->precision_set = true;
		(*format)++;
		data->precision = add_number(format);
	}
	if (is_specifier(**format) == true)
	{
		data->specifier = **format;
		(*format)++;
	}
	else
		*format = initial_format;
}

void	check_flush_insert(t_data *data, char c)
{
	int	bytes_written;

	if (data->current_byte == STASH_SIZE)
	{
		bytes_written = write(1, data->stash, STASH_SIZE);
		data->total_bytes += STASH_SIZE;
		if (bytes_written != STASH_SIZE || data->total_bytes > INT_MAX)
		{
			data->write_failed = true;
			return ;
		}
		data->current_byte = 0;
	}
	data->stash[(data->current_byte)++] = c;
}

static void	insert_specifier_str(t_data *data, va_list *ap)
{
	if (data->specifier == 'c')
		c_handler(data, ap);
	else if (data->specifier == 's')
		s_handler(data, ap);
	else if (data->specifier == 'p')
		p_handler(data, ap);
	else if (data->specifier == 'x' || data->specifier == 'X')
		x_handler(data, ap);
	else if (data->specifier == 'u')
		u_handler(data, ap);
	else if (data->specifier == 'i' || data->specifier == 'd')
		i_d_handler(data, ap);
	else if (data->specifier == '%')
		check_flush_insert(data, '%');
}

static void	fill_stash(const char *format, va_list *ap, t_data *data)
{
	while (*format != '\0' && data->write_failed == false)
	{
		if (*format == '%')
		{
			format++;
			set_format_data(data);
			process_format(&format, data);
			insert_specifier_str(data, ap);
		}
		else
		{
			check_flush_insert(data, *format);
			format++;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_data	data;
	int		total_written;
	int		bytes_written;

	va_start(ap, format);
	set_format_data(&data);
	data.total_bytes = 0;
	data.current_byte = 0;
	data.write_failed = false;
	fill_stash(format, &ap, &data);
	bytes_written = write(1, data.stash, data.current_byte);
	data.total_bytes += data.current_byte;
	if (bytes_written != data.current_byte || data.write_failed == true
		|| data.total_bytes > INT_MAX)
		return (-1);
	total_written = data.total_bytes;
	va_end(ap);
	return (total_written);
}
