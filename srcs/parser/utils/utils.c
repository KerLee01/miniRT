/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	clear_malloc(t_data *data)
{
	t_shape	*current;
	t_shape	*buffer;

	current = data->shape;
	while (current != NULL)
	{
		free(current->data);
		buffer = current;
		current = current->next;
		free(buffer);
	}
	data->shape = NULL;
	if (data->curr_line)
	{
		free(data->curr_line);
		data->curr_line = NULL;
	}
	if (data->fd > 0)
	{
		close(data->fd);
		data->fd = -1;
	}
}

void	clear_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	print_error(t_data *data, char **tokens, char *explicit_err)
{
	int	err_length;

	clear_split(tokens);
	clear_malloc(data);
	write(2, "Error\n", 6);
	if (explicit_err)
	{
		err_length = ft_strlen(explicit_err);
		write(2, explicit_err, err_length);
	}
	exit(1);
}

int	check_normalized_vector(t_coor vec)
{
	if (vec.x < -1.0 || vec.x > 1.0
		|| vec.y < -1.0 || vec.y > 1.0
		|| vec.z < -1.0 || vec.z > 1.0)
		return (0);
	if (dot_product(vec, vec) < 1e-6)
		return (0);
	return (1);
}

double	ft_atof(char *str)
{
	double	value;
	double	dec;
	int		sign;

	value = 0.0;
	dec = 1.0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		value = (value * 10.0) + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		dec *= 10.0;
		value += (*str++ - '0') / dec;
	}
	return (value * sign);
}
