/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 18:35:07 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*location;
	int				found;
	unsigned char	uc;

	found = 0;
	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc % 256)
		{
			location = (char *)s;
			found = 1;
		}
		s++;
	}
	if (*s == '\0' && uc == '\0')
		return ((char *)s);
	if (found == 0)
		return (NULL);
	return (location);
}
