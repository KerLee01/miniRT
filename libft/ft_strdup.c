/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 16:34:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		s_length;
	char	*dup;

	s_length = ft_strlen(s);
	dup = malloc(sizeof(*s) * (s_length + 1));
	if (!dup)
		return (NULL);
	while (*s)
	{
		*dup = *s;
		dup++;
		s++;
	}
	*dup = '\0';
	return (dup - s_length);
}
