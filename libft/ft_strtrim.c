/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 15:43:45 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	in_set(char const *set, char current)
{
	while (*set)
	{
		if (current == *set)
			return (true);
		set++;
	}
	return (false);
}

static int	in_set_front(char const *str, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && in_set(set, str[i]))
	{
		count++;
		i++;
	}
	return (count);
}

static int	in_set_back(char const *str, char const *set)
{
	int	i;
	int	count;

	i = ft_strlen(str) - 1;
	count = 0;
	while (in_set(set, str[i]) && i > -1)
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	j;
	size_t	remove_front;
	size_t	remove_back;
	char	*result;

	i = 0;
	remove_front = in_set_front(s1, set);
	remove_back = in_set_back(s1, set);
	if (remove_front == ft_strlen(s1) || remove_back == ft_strlen(s1))
		return (ft_strdup(""));
	else if (remove_front == 0 && remove_back == 0)
		return (ft_strdup(s1));
	result = malloc(sizeof(char) * (ft_strlen(s1) - (remove_front + remove_back)
				+ 1));
	if (!result)
		return (NULL);
	j = remove_front;
	while (s1[j] != '\0' && j != ft_strlen(s1) - remove_back)
		result[i++] = s1[j++];
	result[i] = '\0';
	return (result);
}
