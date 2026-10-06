#ifndef PARSER_H
#define PARSER_H

#include "rt_structs.h"

//utils.c
void clear_malloc(t_data *data);
void print_error(t_data *data, char **tokens);
void clear_split(char **tokens);
double ft_atof(char *str);
void split_coor(t_coor *element, char *coor, char **tokens, t_data *data);
void split_rgb(t_rgb *element, char *rgb, char **tokens, t_data *data);
int check_normalized_vector(t_coor vec);

// fill_elements.c
void fill_ambient(char *line, t_data *data);
void fill_light(char *line, t_data *data);
void fill_camera(char *line, t_data *data);

// fill_sphere.c
void fill_sphere(char *line, t_data *data);

// fill_plane.c
void fill_plane(char *line, t_data *data);

// fill_cylinder.c
void fill_cylinder(char *line, t_data *data);

// parser.c
void insert_next_shape(t_data *data, t_shape *shape);
void parse_scene(char *file, t_data *data);

#endif
