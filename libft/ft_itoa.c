/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/14 17:40:21 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_int_length(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		int_length;
	long	n_plus;

	n_plus = (long)n;
	int_length = count_int_length(n);
	result = malloc(sizeof(char) * (int_length + 1 + ((n < 0) * 1)));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		n_plus *= -1;
		result[0] = '-';
		result[int_length + 1] = '\0';
	}
	else
		result[int_length--] = '\0';
	if (n == 0)
		result[int_length] = '0';
	while (n_plus != 0)
	{
		result[int_length--] = n_plus % 10 + '0';
		n_plus /= 10;
	}
	return (result);
}
