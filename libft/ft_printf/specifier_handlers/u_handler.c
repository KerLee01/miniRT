/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:47:24 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/16 17:17:19 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_unsigned_length(t_data *data, unsigned int n)
{
	int	length;

	length = 0;
	if (n == 0 && data->precision_set == true && data->precision == 0)
		return (0);
	if (n == 0)
		return (1);
	while (n > 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

static void	insert_unsigned(t_data *data, unsigned int n, int num_length)
{
	if (num_length == 0)
		return ;
	if (n >= 10)
		insert_unsigned(data, n / 10, num_length);
	check_flush_insert(data, (n % 10) + '0');
}

void	u_handler(t_data *data, va_list *ap)
{
	unsigned int	num;
	int				num_length;
	int				width;
	int				num_length_hash;

	num = va_arg(*ap, unsigned int);
	num_length = get_unsigned_length(data, num);
	width = data->width + 1;
	num_length_hash = 0;
	if (data->width_padding == '0' && (data->left_align == true
			|| data->precision_set == true))
		data->width_padding = ' ';
	if (num_length < data->precision)
		num_length = data->precision;
	if (data->hex_hash == true)
		num_length_hash = num_length + 2;
	else
		num_length_hash = num_length;
	while (data->left_align == false && (--(width)-num_length_hash > 0))
		check_flush_insert(data, data->width_padding);
	precision_pad(data, (long)num);
	insert_unsigned(data, num, num_length);
	while (data->left_align == true && (--(width)-num_length_hash > 0))
		check_flush_insert(data, data->width_padding);
}
