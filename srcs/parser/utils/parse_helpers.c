#include "rt.h"

static int	count_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

static char	**get_split_3(char *str, char **tokens, t_data *data)
{
	char	**split;
	int		i;

	if (count_char(str, ',') != 2)
	{
		clear_split(tokens);
		print_error(data);
	}
	split = ft_split(str, ',');
	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i != 3)
	{
		clear_split(tokens);
		clear_split(split);
		print_error(data);
	}
	return (split);
}

void	split_coor(t_coor *element, char *coor, char **tokens, t_data *data)
{
	char	**split;

	split = get_split_3(coor, tokens, data);
	element->x = ft_atof(split[0]);
	element->y = ft_atof(split[1]);
	element->z = ft_atof(split[2]);
	clear_split(split);
}

void	split_rgb(t_rgb *element, char *rgb, char **tokens, t_data *data)
{
	char	**split;

	split = get_split_3(rgb, tokens, data);
	element->r = ft_atoi(split[0]);
	element->g = ft_atoi(split[1]);
	element->b = ft_atoi(split[2]);
	if (element->r < 0 || element->r > 255
		|| element->g < 0 || element->g > 255
		|| element->b < 0 || element->b > 255)
	{
		clear_split(tokens);
		clear_split(split);
		print_error(data);
	}
	clear_split(split);
}
