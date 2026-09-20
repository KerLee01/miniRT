/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/14 10:44:28 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_length;
	int		s2_length;
	char	*result;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	result = malloc(sizeof(*s1) * (s1_length + s2_length + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1_length);
	while (*s2)
	{
		result[s1_length] = *s2;
		s1_length++;
		s2++;
	}
	result[s1_length] = '\0';
	return (result);
}
