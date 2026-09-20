/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:46:54 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/15 20:15:56 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	apply_width(t_data *data, char *s_string, int s_length)
{
	int	i;
	int	width;

	i = -1;
	width = data->width + 1;
	while (data->left_align == false && --width - s_length > 0)
		check_flush_insert(data, ' ');
	while (s_string[++i] != '\0')
		check_flush_insert(data, s_string[i]);
	while (data->left_align == true && --width - s_length > 0)
		check_flush_insert(data, ' ');
}

static void	apply_width_precision(t_data *data, char *s_string)
{
	int	i;
	int	width;

	i = -1;
	width = data->width + 1;
	while (data->left_align == false && --width - data->precision > 0)
		check_flush_insert(data, ' ');
	while (++i < data->precision)
		check_flush_insert(data, s_string[i]);
	while (data->left_align == true && (--width) - data->precision > 0)
		check_flush_insert(data, ' ');
}

static void	process_to_main_string(t_data *data, char *s_string, int s_length)
{
	int	i;

	i = 0;
	while (data->precision_set == false && data->width == 0
		&& s_string[i] != '\0')
	{
		check_flush_insert(data, s_string[i]);
		i++;
	}
	while (data->width == 0 && data->precision == s_length
		&& i < data->precision)
	{
		check_flush_insert(data, s_string[i]);
		i++;
	}
	if (data->precision_set == false && data->width - s_length > 0)
		apply_width(data, s_string, s_length);
	else if (data->width > data->precision && data->precision == s_length)
		apply_width_precision(data, s_string);
}

void	s_handler(t_data *data, va_list *ap)
{
	char	*s_string;
	int		s_length;

	s_string = va_arg(*ap, char *);
	if (s_string == NULL && (data->precision_set == false
			|| data->precision >= 6))
		s_string = "(null)";
	else if (s_string == NULL && data->precision_set == true
		&& data->precision < 7)
		s_string = "";
	s_length = ft_strlen(s_string);
	if (data->precision >= s_length)
		data->precision_set = false;
	else if (data->precision_set == true)
		s_length = data->precision;
	if (data->width - s_length <= 0)
		data->width = 0;
	process_to_main_string(data, s_string, s_length);
}
