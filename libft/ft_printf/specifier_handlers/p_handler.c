/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:45:05 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/15 17:45:07 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_addr_length(unsigned long addr)
{
	int	length;

	length = 2;
	if (addr == 0)
		return (5);
	while (addr > 0)
	{
		length++;
		addr /= 16;
	}
	return (length);
}

static void	insert_null(t_data *data)
{
	char	*str;

	str = "(nil)";
	while (*str)
	{
		check_flush_insert(data, *str);
		str++;
	}
}

static void	insert_addr(t_data *data, unsigned long num)
{
	char	*base;

	base = "0123456789abcdef";
	if (num >= 16)
		insert_addr(data, num / 16);
	check_flush_insert(data, base[num % 16]);
}

void	p_handler(t_data *data, va_list *ap)
{
	void			*ptr;
	int				width;
	int				hex_length;
	unsigned long	address;

	ptr = va_arg(*ap, void *);
	if (data->width > 0)
		width = data->width + 1;
	else
		width = 1;
	address = (unsigned long)ptr;
	hex_length = get_addr_length(address);
	while (data->left_align == false && (--(width)-hex_length) > 0)
		check_flush_insert(data, ' ');
	if (ptr == NULL)
		insert_null(data);
	else
	{
		check_flush_insert(data, '0');
		check_flush_insert(data, 'x');
		insert_addr(data, address);
	}
	while (data->left_align == true && (--(width)-hex_length) > 0)
		check_flush_insert(data, ' ');
}
