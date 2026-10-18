/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:37:44 by kerlee            #+#    #+#             */
/*   Updated: 2026/10/18 12:08:22 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_bonus.h"
#include "mlx.h"
#include <stdlib.h>

int	close_window(t_data *data)
{
	clear_malloc(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if(data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		close_window(data);
	return (0);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		print_error(data, NULL, "mlx_init() fail\n");
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data->win)
		print_error(data, NULL, "mlx_new_window() fail\n");
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		print_error(data, NULL, "mlx_new_image() fail\n");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		print_error(data, NULL, "mlx_get_data_addr() fail\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./miniRT_bonus <file.rt>\n", 39);
		return (1);
	}
	parse_scene(argv[1], &data);
	gimbal_lock_check(&data.cam);
	find_right_axis(&data.cam);
	find_true_up(&data.cam);
	calculate_viewport(&data.cam);
	init_mlx(&data);
	render_scene(&data);
	mlx_hook(data.win, 17, 0, (int (*)())(void *)close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, (int (*)())(void *)key_hook, &data);
	mlx_hook(data.win, 12, 1L << 15, (int (*)())(void *)expose_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
