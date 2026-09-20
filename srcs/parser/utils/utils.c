#include "rt.h"

void clear_malloc(t_data *data)
{
	t_shape *current;
	t_shape *buffer;

	current = data->shape;
	if(current == NULL)
		return;
	while(current != NULL)
	{
		free(current->data);
		buffer = current;
		current = current->next;
		free(buffer);
	}
}

void print_error(t_data *data)
{
	int i;

	clear_malloc(data);
	i = write(2, "Error\n", 6);
	(void)i;
	exit(1);
}

void clear_split(char **tokens)
{
	int i;

	i = 0;
	while(tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

double ft_atof(char *str)
{
	double value;
	double decimal_inc;
	int negative;

	value = 0.0;
	decimal_inc = 1.0;
	negative = 1;
	if(*str == '-')
	{
		negative = -1;
		str++;
	}
	while(*str >= '0' && *str <= '9')
	{
		value = (value * 10.0) + (*str - '0');
		str++;
	}
	if(*str == '.')
		str++;
	while(*str >= '0' && *str <= '9')
	{
		decimal_inc *= 10.0;
		value += (*str - '0') / decimal_inc;
		str++;
	}
	return (value * negative);
}

int check_normalized_vector(t_coor vec)
{
    if (vec.x < -1.0 || vec.x > 1.0 || 
        vec.y < -1.0 || vec.y > 1.0 || 
        vec.z < -1.0 || vec.z > 1.0)
        return (0);
        
    if (vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0)
        return (0);
        
    return (1);
}

void split_coor(t_coor *element, char *coor, char **tokens, t_data *data)
{
	int i;
	char **split;

	i = 0;
	split = ft_split(coor, ',');
	while(split[i] != NULL)
		i++;
	if(i != 3)
	{
		clear_split(tokens);
		clear_split(split);
		print_error(data);
	}
	element->x = ft_atof(split[0]);
	element->y = ft_atof(split[1]);
	element->z = ft_atof(split[2]);
	clear_split(split);
}

void split_rgb(t_rgb *element, char *rgb, char **tokens, t_data *data)
{
	int i;
	char **split;

	i = 0;
	split = ft_split(rgb, ',');
	while(split[i] != NULL)
		i++;
	if(i != 3)
	{
		clear_split(tokens);
		clear_split(split);
		print_error(data);
	}
	element->r = ft_atoi(split[0]);
	element->g = ft_atoi(split[1]);
	element->b = ft_atoi(split[2]);
	if(!(element->r >= 0 && element->r <= 255))
		print_error(data);
	if(!(element->g >= 0 && element->g <= 255))
		print_error(data);
	if(!(element->b >= 0 && element->b <= 255))
		print_error(data);
	clear_split(split);
}
