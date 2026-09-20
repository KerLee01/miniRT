/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:44:28 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/15 17:44:39 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	c_handler(t_data *data, va_list *ap)
{
	char	c;
	int		width;

	c = va_arg(*ap, int);
	width = data->width + 1;
	if (width - 1 > 1)
	{
		while (data->left_align == false && --(width) > 1)
			check_flush_insert(data, ' ');
		check_flush_insert(data, c);
		while (data->left_align == true && --(width) > 1)
			check_flush_insert(data, ' ');
	}
	else
		check_flush_insert(data, c);
}
