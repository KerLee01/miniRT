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

void print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
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
	line = get_next_line(fd);
	while(line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

