/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_X_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:47:35 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/16 17:21:16 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_hex_length(t_data *data, unsigned long hex)
{
	int	length;

	length = 0;
	if (hex == 0 && data->precision_set == true && data->precision == 0)
		return (0);
	if (hex == 0)
		return (1);
	while (hex > 0)
	{
		length++;
		hex /= 16;
	}
	return (length);
}

static void	insert_hex(t_data *data, unsigned long num, int hex_length)
{
	char	*base;

	base = "0123456789abcdef";
	if (data->specifier == 'X')
		base = "0123456789ABCDEF";
	if (hex_length == 0)
		return ;
	if (num >= 16)
		insert_hex(data, num / 16, hex_length);
	check_flush_insert(data, base[num % 16]);
}

static void	insert_hash(t_data *data)
{
	check_flush_insert(data, '0');
	check_flush_insert(data, data->specifier);
}

static int	length_with_hash(t_data *data, int hex_length, unsigned long hex)
{
	int	hex_length_hash;

	hex_length_hash = hex_length;
	if (data->hex_hash == true && hex != 0)
		hex_length_hash = hex_length + 2;
	return (hex_length_hash);
}

void	x_handler(t_data *data, va_list *ap)
{
	unsigned long	hex;
	int				hex_length;
	int				hex_length_hash;
	int				width;

	hex = va_arg(*ap, unsigned int);
	width = data->width + 1;
	hex_length = get_hex_length(data, hex);
	if (hex_length < data->precision)
		hex_length = data->precision;
	if (data->width_padding == '0' && (data->left_align == true
			|| data->precision_set == true))
		data->width_padding = ' ';
	hex_length_hash = length_with_hash(data, hex_length, hex);
	if (data->width_padding == '0' && data->hex_hash == true && hex != 0)
		insert_hash(data);
	while (data->left_align == false && (--(width)-hex_length_hash) > 0)
		check_flush_insert(data, data->width_padding);
	if (data->width_padding == ' ' && data->hex_hash == true && hex != 0)
		insert_hash(data);
	precision_pad(data, (long)hex);
	insert_hex(data, hex, hex_length);
	while (data->left_align == true && (--(width)-hex_length_hash) > 0)
		check_flush_insert(data, data->width_padding);
}
