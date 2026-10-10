#include "rt_bonus.h"

static void	if_not_normalized_free(t_data *data, char **tokens,
		t_shape *plane, t_plane *plane_data)
{
	if (check_normalized_vector(plane_data->forward) == 0)
	{
		free(plane_data);
		free(plane);
		print_error(data, tokens, "Invalid data found\n");
	}
}

static void	fill_data_attach_node(t_data *data, char **tokens)
{
	t_shape	*plane;
	t_plane	*plane_data;

	plane = malloc(sizeof(t_shape));
	if (!plane)
		print_error(data, tokens, "Malloc fail\n");
	plane_data = malloc(sizeof(t_plane));
	if (!plane_data)
	{
		free(plane);
		print_error(data, tokens, "Malloc fail\n");
	}
	plane->type = PLANE;
	plane->data = plane_data;
	split_coor(&plane_data->point, tokens[1], tokens, data);
	split_coor(&plane_data->forward, tokens[2], tokens, data);
	if_not_normalized_free(data, tokens, plane, plane_data);
	plane_data->forward = normalization(plane_data->forward);
	split_rgb(&plane_data->rgb, tokens[3], tokens, data);
	plane->next = NULL;
	insert_next_shape(data, plane);
}

void	fill_plane(char *line, t_data *data)
{
	int		i;
	char	**tokens;

	i = 0;
	tokens = ft_split(line, ' ');
	if (!tokens)
		print_error(data, NULL, "ft_split() fail\n");
	while (tokens[i] != NULL)
		i++;
	if (i != 4)
		print_error(data, tokens, "Additional/Lesser data required\n");
	fill_data_attach_node(data, tokens);
	clear_split(tokens);
}
