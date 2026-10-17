/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "get_next_line.h"
#include "fcntl.h"

static int	check_valid_rt(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (1);
	if (ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (1);
	return (0);
}

static void	sanitize_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\r' || line[i] == '\n'
			|| line[i] == '\v' || line[i] == '\f')
			line[i] = ' ';
		i++;
	}
}

void	insert_next_shape(t_data *data, t_shape *shape)
{
	t_shape	*current;

	if (data->shape == NULL)
	{
		data->shape = shape;
		return ;
	}
	current = data->shape;
	while (current->next != NULL)
		current = current->next;
	current->next = shape;
}

int	find_and_fill_element(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	if (ft_strncmp(&line[i], "A ", 2) == 0)
		fill_ambient(&line[i], data);
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		fill_camera(&line[i], data);
	else if (ft_strncmp(&line[i], "L ", 2) == 0)
		fill_light(&line[i], data);
	else if (ft_strncmp(&line[i], "sp ", 3) == 0)
		fill_sphere(&line[i], data);
	else if (ft_strncmp(&line[i], "pl ", 3) == 0)
		fill_plane(&line[i], data);
	else if (ft_strncmp(&line[i], "cy ", 3) == 0)
		fill_cylinder(&line[i], data);
	else
		return (1);
	return (0);
}

void	parse_scene(char *file, t_data *data)
{
	if (check_valid_rt(file) != 0)
		print_error(data, NULL, "Invalid file\n");
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		print_error(data, NULL, "Invalid fd\n");
	data->curr_line = get_next_line(data->fd);
	while (data->curr_line != NULL)
	{
		sanitize_line(data->curr_line);
		if (find_and_fill_element(data->curr_line, data) == 1)
			print_error(data, NULL, "Empty file/Invalid elements found\n");
		free(data->curr_line);
		data->curr_line = get_next_line(data->fd);
	}
	close(data->fd);
	data->fd = -1;
	if (data->cam.filled == 0 || data->ambient.filled == 0
		|| data->light.filled == 0)
		print_error(data, NULL, "One or more element A/C/L is missing\n");
}
