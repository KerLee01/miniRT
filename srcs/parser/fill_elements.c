#include "rt.h"

static char	**get_valid_tokens(char *line, int expected, t_data *data)
{
	char	**tokens;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens)
		print_error(data);
	i = 0;
	while (tokens[i] != NULL)
		i++;
	if (i != expected)
	{
		clear_split(tokens);
		print_error(data);
	}
	return (tokens);
}

void	fill_ambient(char *line, t_data *data)
{
	char	**tokens;

	if (data->ambient.filled == 1)
		print_error(data);
	data->ambient.filled = 1;
	tokens = get_valid_tokens(line, 3, data);
	data->ambient.ratio = ft_atof(tokens[1]);
	if (!(data->ambient.ratio >= 0.0 && data->ambient.ratio <= 1.0))
	{
		clear_split(tokens);
		print_error(data);
	}
	split_rgb(&data->ambient.rgb, tokens[2], tokens, data);
	clear_split(tokens);
}

void	fill_light(char *line, t_data *data)
{
	char	**tokens;

	if (data->light.filled == 1)
		print_error(data);
	data->light.filled = 1;
	tokens = get_valid_tokens(line, 4, data);
	split_coor(&data->light.position, tokens[1], tokens, data);
	data->light.bright_ratio = ft_atof(tokens[2]);
	if (!(data->light.bright_ratio >= 0.0 && data->light.bright_ratio <= 1.0))
	{
		clear_split(tokens);
		print_error(data);
	}
	split_rgb(&data->light.rgb, tokens[3], tokens, data);
	clear_split(tokens);
}

void	fill_camera(char *line, t_data *data)
{
	char	**tokens;

	if (data->cam.filled == 1)
		print_error(data);
	data->cam.filled = 1;
	tokens = get_valid_tokens(line, 4, data);
	split_coor(&data->cam.origin, tokens[1], tokens, data);
	split_coor(&data->cam.forward, tokens[2], tokens, data);
	if (check_normalized_vector(data->cam.forward) == 0)
	{
		clear_split(tokens);
		print_error(data);
	}
	data->cam.forward = normalization(data->cam.forward);
	data->cam.fov = ft_atoi(tokens[3]);
	if (!(data->cam.fov >= 0 && data->cam.fov <= 180))
	{
		clear_split(tokens);
		print_error(data);
	}
	clear_split(tokens);
}
