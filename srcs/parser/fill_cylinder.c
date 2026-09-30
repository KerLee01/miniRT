#include "rt.h"

static void	fill_data_attach_node(t_data *data, char **tokens)
{
	t_shape		*cylinder;
	t_cylinder	*cylinder_data;

	cylinder = malloc(sizeof(t_shape));
	if (!cylinder)
	{
		clear_split(tokens);
		print_error(data);
	}
	cylinder_data = malloc(sizeof(t_cylinder));
	if (!cylinder_data)
	{
		free(cylinder);
		clear_split(tokens);
		print_error(data);
	}
	cylinder->type = CYLINDER;
	cylinder->data = cylinder_data;
	split_coor(&cylinder_data->center, tokens[1], tokens, data);
	split_coor(&cylinder_data->forward, tokens[2], tokens, data);
	if (check_normalized_vector(cylinder_data->forward) == 0)
	{
		free(cylinder_data);
		free(cylinder);
		clear_split(tokens);
		print_error(data);
	}
	cylinder_data->forward = normalization(cylinder_data->forward);
	cylinder_data->radius = ft_atof(tokens[3]) / 2.0;
	cylinder_data->height = ft_atof(tokens[4]);
	if (cylinder_data->radius <= 0.0 || cylinder_data->height <= 0.0)
	{
		free(cylinder_data);
		free(cylinder);
		clear_split(tokens);
		print_error(data);
	}
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
		print_error(data);
	while (tokens[i] != NULL)
		i++;
	if (i != 6)
	{
		clear_split(tokens);
		print_error(data);
	}
	fill_data_attach_node(data, tokens);
	clear_split(tokens);
}
