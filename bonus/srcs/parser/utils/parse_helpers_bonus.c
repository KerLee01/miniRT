#include "rt_bonus.h"

int	is_valid_num(char *str, int allow_dot)
{
	int	dots;
	int	has_digit;

	dots = 0;
	has_digit = 0;
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str == '.' && allow_dot)
			dots++;
		else if (*str >= '0' && *str <= '9')
			has_digit = 1;
		else
			return (0);
		str++;
	}
	return (has_digit && dots <= allow_dot);
}

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
		print_error(data, tokens, "Invalid data found\n");
	split = ft_split(str, ',');
	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i != 3)
	{
		clear_split(split);
		print_error(data, tokens, "Additional/Lesser data required\n");
	}
	return (split);
}

void	split_coor(t_coor *element, char *coor, char **tokens, t_data *data)
{
	char	**split;

	split = get_split_3(coor, tokens, data);
	if (!is_valid_num(split[0], 1) || !is_valid_num(split[1], 1)
		|| !is_valid_num(split[2], 1))
	{
		clear_split(split);
		print_error(data, tokens, "Invalid data found\n");
	}
	element->x = ft_atof(split[0]);
	element->y = ft_atof(split[1]);
	element->z = ft_atof(split[2]);
	clear_split(split);
}

void	split_rgb(t_rgb *element, char *rgb, char **tokens, t_data *data)
{
	char	**split;

	split = get_split_3(rgb, tokens, data);
	if (!is_valid_num(split[0], 0) || !is_valid_num(split[1], 0)
		|| !is_valid_num(split[2], 0))
	{
		clear_split(split);
		print_error(data, tokens, "Invalid data found\n");
	}
	element->r = ft_atoi(split[0]);
	element->g = ft_atoi(split[1]);
	element->b = ft_atoi(split[2]);
	if (element->r < 0 || element->r > 255
		|| element->g < 0 || element->g > 255
		|| element->b < 0 || element->b > 255)
	{
		clear_split(split);
		print_error(data, tokens, "Invalid data found\n");
	}
	clear_split(split);
}
