/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_and_display_error(t_shape *cylinder,
		t_cylinder *cylinder_data, t_data *data, char **tokens)
{
	free(cylinder_data);
	free(cylinder);
	print_error(data, tokens, "Invalid data found\n");
}

static void	check_radius_height(t_shape *cylinder,
		t_cylinder *cylinder_data, t_data *data, char **tokens)
{
	if (cylinder_data->radius <= 0.0 || cylinder_data->height <= 0.0)
		free_and_display_error(cylinder, cylinder_data, data, tokens);
}

static void	fill_data_attach_node(t_data *data, char **tokens)
{
	t_shape		*cylinder;
	t_cylinder	*cylinder_data;

	cylinder = malloc(sizeof(t_shape));
	if (!cylinder)
		print_error(data, tokens, "Malloc fail\n");
	cylinder_data = malloc(sizeof(t_cylinder));
	if (!cylinder_data)
	{
		free(cylinder);
		print_error(data, tokens, "Malloc fail\n");
	}
	cylinder->type = CYLINDER;
	cylinder->data = cylinder_data;
	split_coor(&cylinder_data->center, tokens[1], tokens, data);
	split_coor(&cylinder_data->forward, tokens[2], tokens, data);
	if (check_normalized_vector(cylinder_data->forward) == 0)
		free_and_display_error(cylinder, cylinder_data, data, tokens);
	cylinder_data->forward = normalization(cylinder_data->forward);
	cylinder_data->radius = ft_atof(tokens[3]) / 2.0;
	cylinder_data->height = ft_atof(tokens[4]);
	check_radius_height(cylinder, cylinder_data, data, tokens);
	split_rgb(&cylinder_data->rgb, tokens[5], tokens, data);
	cylinder->next = NULL;
	insert_next_shape(data, cylinder);
}

void	fill_cylinder(char *line, t_data *data)
{
	int		i;
	char	**tokens;

	i = 0;
	tokens = ft_split(line, ' ');
	if (!tokens)
		print_error(data, NULL, "ft_split() fail\n");
	while (tokens[i] != NULL)
		i++;
	if (i != 6 || !is_valid_num(tokens[3], 1) || !is_valid_num(tokens[4], 1))
		print_error(data, tokens, "Additional/Lesser data required\n");
	fill_data_attach_node(data, tokens);
	clear_split(tokens);
}
