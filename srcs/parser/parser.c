#include "rt.h"
#include "get_next_line.h"
#include "fcntl.h"

static int check_valid_rt(char *file)
{
	int len;

	len = ft_strlen(file);
	if(len < 4)
		return (0);
	if(file[len - 3] == '.' && file[len - 2] == "r" && file[len - 4] == "t")
		return (1);
	return (0);
}

void insert_next_shape(t_data *data, t_shape *shape)
{
	t_shape *current;

	if(data->shape == NULL)
	{
		data->shape = shape;
		return;
	}

	current = data->shape;
	while(current->next != NULL)
		current = current->next;
	current->next = shape;
}

int find_and_fill_element(char *line, t_data *data)
{
	int i;

	i = 0;
	while(line[i] == ' )
		i++;
	if(line[i] == '\n')
		return(1);
	if(ft_strncmp(&line[i], "A", 1) == 0)
		fill_ambient(&line[i], data);
	else if(ft_strncmp(&line[i], "C", 1) == 0)
		fill_camera(&line[i], data);
	else if(ft_strncmp(&line[i], "L", 1) == 0)
		fill_light(&line[i], data);
	else if(ft_strncmp(&line[i], "sp", 2) == 0)
		fill_sphere(&line[i], data);
	else if(ft_strncmp(&line[i], "pl", 2) == 0)
		fill_plane(&line[i], data);
	else if(ft_strncmp(&line[i], "cy", 2) == 0)
		fill_cylinder(&line[i], data);
	else
		return (1);
	return (0);
}

void parse_scene(char *file, t_data *data)
{
	int fd;
	char *line;

	if(check_valid_rt(file) == 0)
		print_error();
	fd = open(file, O_RDONLY);
	if(fd < 0)
		print_error();
	ft_bzero(data, sizeof(t_data));
	line = get_next_line(fd);
	while(line != NULL)
	{
		if(line[0] != '\n')
		{
			if(find_and_fill_element(line, data) == 1)
				print_error();
		}
		free(line);
		line = get_next_line(fd);
	}
	if(data->cam.filled == 0 || data->ambient.filled == 0 || data->light.filled == 0)
		print_error(data);
	close(fd);
}

