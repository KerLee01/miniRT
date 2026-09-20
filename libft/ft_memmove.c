/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 16:52:14 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;

	if (dest == NULL && src == NULL)
		return (NULL);
	destination = (char *)dest;
	source = (const char *)src;
	if (n == 0)
		return (dest);
	if ((destination > source) && (destination < source + n))
	{
		destination += n - 1;
		source += n - 1;
		while (n--)
			*destination-- = *source--;
	}
	else
	{
		while (n != 0)
		{
			*destination++ = *source++;
			n--;
		}
	}
	return (dest);
}
