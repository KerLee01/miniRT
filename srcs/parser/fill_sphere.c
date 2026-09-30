#include "rt.h"

static void	fill_data_attach_node(t_data *data, char **tokens)
{
	t_shape		*sphere;
	t_sphere	*sphere_data;

	sphere = malloc(sizeof(t_shape));
	if (!sphere)
	{
		clear_split(tokens);
		print_error(data);
	}
	sphere_data = malloc(sizeof(t_sphere));
	if (!sphere_data)
	{
		free(sphere);
		clear_split(tokens);
		print_error(data);
	}
	sphere->type = SPHERE;
	sphere->data = sphere_data;
	split_coor(&sphere_data->center, tokens[1], tokens, data);
	sphere_data->radius = ft_atof(tokens[2]) / 2.0;
	if (sphere_data->radius <= 0.0)
	{
		free(sphere_data);
		free(sphere);
		clear_split(tokens);
		print_error(data);
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
		print_error(data);
	while (tokens[i] != NULL)
		i++;
	if (i != 4)
	{
		clear_split(tokens);
		print_error(data);
	}
	fill_data_attach_node(data, tokens);
	clear_split(tokens);
}
