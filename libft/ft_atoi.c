/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 14:31:35 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		negative;

	result = 0;
	negative = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (!(*(str + 1) >= '0' && *(str + 1) <= '9'))
			return (0);
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		if (result > 2147483647L)
			break ;
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result * negative > 2147483647L || result * negative < -2147483648L)
		return (-1);
	return ((int)(result * negative));
}
