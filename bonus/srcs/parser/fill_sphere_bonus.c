/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sphere_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/18 18:28:49 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_bonus.h"

static void	fill_data_attach_node(t_data *data, char **tokens)
{
	t_shape		*sphere;
	t_sphere	*sphere_data;

	sphere = malloc(sizeof(t_shape));
	if (!sphere)
		print_error(data, tokens, "Malloc fail\n");
	sphere_data = malloc(sizeof(t_sphere));
	if (!sphere_data)
	{
		free(sphere);
		print_error(data, tokens, "Malloc fail\n");
	}
	sphere->type = SPHERE;
	sphere->data = sphere_data;
	split_coor(&sphere_data->center, tokens[1], tokens, data);
	sphere_data->radius = ft_atof(tokens[2]) / 2.0;
	if (sphere_data->radius <= 0.0)
	{
		free(sphere_data);
		free(sphere);
		print_error(data, tokens, "Invalid data found\n");
	}
	split_rgb(&sphere_data->rgb, tokens[3], tokens, data);
	sphere->next = NULL;
	insert_next_shape(data, sphere);
}

void	fill_sphere(char *line, t_data *data)
{
	int		i;
	char	**tokens;

	i = 0;
	tokens = ft_split(line, ' ');
	if (!tokens)
		print_error(data, NULL, "ft_split() fail\n");
	while (tokens[i] != NULL)
		i++;
	if (i != 4 || !is_valid_num(tokens[2], 1))
		print_error(data, tokens, "Additional/Lesser data required\n");
	fill_data_attach_node(data, tokens);
	clear_split(tokens);
}
