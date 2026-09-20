/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_d_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:47:16 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/16 17:16:55 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_num_length(t_data *data, long num)
{
	int	format_length;
	int	num_length;

	format_length = 0;
	num_length = 0;
	if (num == 0 && data->precision_set == true && data->precision == 0)
		return (0);
	if (num < 0)
	{
		num *= -1;
		format_length++;
	}
	else if (data->show_sign == true || data->if_positive_space == true)
		format_length++;
	if (num == 0 && data->precision_set == false)
		return (format_length + 1);
	while (num > 0)
	{
		num /= 10;
		num_length++;
	}
	if (num_length < data->precision)
		return (format_length + data->precision);
	return (format_length + num_length);
}

static void	insert_num(t_data *data, long num, int num_length)
{
	if (num_length == 0)
		return ;
	if (num < 0)
		num *= -1;
	if (num >= 10)
		insert_num(data, num / 10, num_length);
	check_flush_insert(data, (num % 10) + '0');
}

static void	insert_sign_space(t_data *data, int num)
{
	if (num < 0)
		check_flush_insert(data, '-');
	if (data->show_sign == true && num >= 0)
		check_flush_insert(data, '+');
	if (data->if_positive_space == true && num >= 0)
		check_flush_insert(data, ' ');
}

void	i_d_handler(t_data *data, va_list *ap)
{
	int	num;
	int	num_length;
	int	width;

	num = va_arg(*ap, int);
	width = data->width + 1;
	if (data->show_sign == true && data->if_positive_space == true)
		data->if_positive_space = false;
	if (data->width_padding == '0' && (data->precision_set == true
			|| data->left_align == true))
		data->width_padding = ' ';
	num_length = get_num_length(data, (long)num);
	if (data->width_padding == '0')
		insert_sign_space(data, num);
	while (data->left_align == false && (--(width)-num_length) > 0)
		check_flush_insert(data, data->width_padding);
	if (data->width_padding == ' ')
		insert_sign_space(data, num);
	precision_pad(data, (long)num);
	insert_num(data, (long)num, num_length);
	while (data->left_align == true && (--(width)-num_length) > 0)
		check_flush_insert(data, data->width_padding);
}
