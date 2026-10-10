#include "rt_bonus.h"

static char	**get_valid_tokens(char *line, int expected, t_data *data)
{
	char	**tokens;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens)
		print_error(data, NULL, "ft_split() fail\n");
	i = 0;
	while (tokens[i] != NULL)
		i++;
	if (i != expected)
		print_error(data, tokens, "Additional/Lesser data required\n");
	return (tokens);
}

void	fill_ambient(char *line, t_data *data)
{
	char	**tokens;

	if (data->ambient.filled == 1)
		print_error(data, NULL, "Too many elements 'A'\n");
	data->ambient.filled = 1;
	tokens = get_valid_tokens(line, 3, data);
	if (!is_valid_num(tokens[1], 1))
		print_error(data, tokens, "Invalid data found\n");
	data->ambient.ratio = ft_atof(tokens[1]);
	if (!(data->ambient.ratio >= 0.0 && data->ambient.ratio <= 1.0))
		print_error(data, tokens, "Invalid data found\n");
	split_rgb(&data->ambient.rgb, tokens[2], tokens, data);
	clear_split(tokens);
}

void	add_light_node(t_light **lst, t_light *node)
{
	t_light	*current;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

void	fill_light(char *line, t_data *data)
{
	char	**tokens;
	t_light	*new_light;

	tokens = get_valid_tokens(line, 4, data);
	new_light = malloc(sizeof(t_light));
	if (!new_light)
		print_error(data, tokens, "Malloc fail\n");
	new_light->next = NULL;
	add_light_node(&data->light, new_light);
	split_coor(&new_light->position, tokens[1], tokens, data);
	if (!is_valid_num(tokens[2], 1))
		print_error(data, tokens, "Invalid data found\n");
	new_light->bright_ratio = ft_atof(tokens[2]);
	if (!(new_light->bright_ratio >= 0.0 && new_light->bright_ratio <= 1.0))
		print_error(data, tokens, "Invalid data found\n");
	split_rgb(&new_light->rgb, tokens[3], tokens, data);
	clear_split(tokens);
}

void	fill_camera(char *line, t_data *data)
{
	char	**tokens;

	if (data->cam.filled == 1)
		print_error(data, NULL, "Too many elements 'C'\n");
	data->cam.filled = 1;
	tokens = get_valid_tokens(line, 4, data);
	split_coor(&data->cam.origin, tokens[1], tokens, data);
	split_coor(&data->cam.forward, tokens[2], tokens, data);
	if (check_normalized_vector(data->cam.forward) == 0)
		print_error(data, tokens, "Invalid data found\n");
	data->cam.forward = normalization(data->cam.forward);
	if (!is_valid_num(tokens[3], 0))
		print_error(data, tokens, "Invalid data found\n");
	data->cam.fov = ft_atoi(tokens[3]);
	if (!(data->cam.fov >= 0 && data->cam.fov <= 180))
		print_error(data, tokens, "Invalid data found\n");
	clear_split(tokens);
}
