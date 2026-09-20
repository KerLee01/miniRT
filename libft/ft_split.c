/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <kerlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:05 by kerlee            #+#    #+#             */
/*   Updated: 2025/11/17 20:27:30 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_char(char a, char c)
{
	if (a == c)
		return (true);
	return (false);
}

static int	count_split(char const *s, char c)
{
	int	i;
	int	split_count;
	int	not_char_count;

	i = 0;
	split_count = 0;
	not_char_count = 0;
	while (s[i] != '\0')
	{
		if (is_char(s[i], c) == false)
			not_char_count++;
		if (is_char(s[i], c) == true && not_char_count > 0)
		{
			split_count++;
			not_char_count = 0;
		}
		i++;
	}
	if (not_char_count != 0)
		split_count++;
	return (split_count);
}

static void	free_splits(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	find_splits(char **all_split, char const *s, char c, int *j)
{
	int		k;
	int		length;
	char	*str;

	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		length = 0;
		while (s[length] != c && s[length] != '\0')
			length++;
		str = malloc(sizeof(char) * (length + 1));
		if (!str)
			return ;
		k = 0;
		while (k < length)
		{
			str[k++] = *s;
			s++;
		}
		str[k] = '\0';
		all_split[(*j)++] = str;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**all_split;
	int		j;

	j = 0;
	if (count_split(s, c) == 0)
	{
		all_split = malloc(sizeof(char *));
		if (!all_split)
			return (NULL);
	}
	else
	{
		all_split = malloc(sizeof(char *) * (count_split(s, c) + 1));
		if (!all_split)
			return (NULL);
		find_splits(all_split, s, c, &j);
		if (j != count_split(s, c))
		{
			free_splits(all_split, j);
			return (NULL);
		}
	}
	all_split[j] = NULL;
	return (all_split);
}
