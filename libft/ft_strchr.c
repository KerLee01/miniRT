/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 18:35:29 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;
	char			*str;

	str = (char *)s;
	uc = (unsigned char)c;
	while (*str)
	{
		if (*str == uc % 256)
			return (str);
		str++;
	}
	if (*str == '\0' && uc == '\0')
		return (str);
	return (NULL);
}
