/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:18:06 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/15 18:20:57 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	is_flag(char c, t_data *data)
{
	if (c == ' ')
		return (data->if_positive_space = true, true);
	if (c == '+')
		return (data->show_sign = true, true);
	if (c == '#')
		return (data->hex_hash = true, true);
	if (c == '-')
		return (data->left_align = true, true);
	if (c == '0')
		return (data->width_padding = '0', true);
	return (false);
}

bool	is_specifier(char s)
{
	if (s == 'c' || s == 's' || s == 'p' || s == 'd' || s == 'i' || s == 'u'
		|| s == 'x' || s == 'X' || s == '%')
		return (true);
	return (false);
}

void	set_format_data(t_data *data)
{
	data->if_positive_space = false;
	data->show_sign = false;
	data->hex_hash = false;
	data->left_align = false;
	data->precision_set = false;
	data->width_padding = ' ';
	data->precision = 0;
	data->specifier = 0;
}

int	add_number(const char **format)
{
	int	result;

	result = 0;
	while (**format >= '0' && **format <= '9')
	{
		result *= 10;
		result += (**format - '0');
		(*format)++;
	}
	return (result);
}
