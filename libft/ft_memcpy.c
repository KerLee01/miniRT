/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 16:54:10 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;
	int			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	destination = (char *)dest;
	source = (const char *)src;
	if (n == 0)
		return (dest);
	while (n != 0)
	{
		destination[i] = *source;
		i++;
		source++;
		n--;
	}
	return (dest);
}
