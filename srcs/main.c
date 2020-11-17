/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:17:59 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:57:42 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_info	g_info;

void	draw(t_info *info)
{
	int			x;
	int			y;

	y = 0;
	while (y < info->cub->render_size_y)
	{
		x = 0;
		while (x < info->cub->render_size_x)
		{
			info->img.data[y * info->cub->render_size_x + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	int			x;
	int			i;

	x = 0;
	while (x < info->cub->render_size_x)
		floor_ceiling_to_buffer(info, x++);
	x = 0;
	while (x < info->cub->render_size_x)
		wall_to_buffer(info, x++);
	i = 0;
	while (i < info->cub->sprite_count)
	{
		info->sprite[i].distance =
			((info->pos_x - info->sprite[i].x) \
			* (info->pos_x - info->sprite[i].x) \
			+ (info->pos_y - info->sprite[i].y) \
			* (info->pos_y - info->sprite[i].y));
		i++;
	}
	sort_sprites(info);
	i = 0;
	while (i < info->cub->sprite_count)
		draw_sprite(info, i++);
}

int		key_press(int key, t_info *info)
{
	if (key == KEY_W)
		move_player_w(info);
	else if (key == KEY_A)
		move_player_a(info);
	else if (key == KEY_S)
		move_player_s(info);
	else if (key == KEY_D)
		move_player_d(info);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		move_player_arrow(info, key);
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}

int		main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		g_info.mlx = mlx_init();
		init_info(&g_info, argv[1]);
		init_info_rest(&g_info);
		mlx_loop_hook(g_info.mlx, main_loop, &g_info);
		mlx_hook(g_info.win, X_EVENT_KEY_PRESS, 1, key_press, &g_info);
		mlx_hook(g_info.win, X_EVENT_KEY_EXIT, 1L << 5, screen_exit, &g_info);
		mlx_loop(g_info.mlx);
	}
	else if (argc == 3 && ft_strlen(argv[2]) == 6
			&& ft_strncmp(argv[2], "--save", 6) == 0)
		bmp_main(&g_info, argv[1]);
	else
		error_exit(".cub file does not exist");
	return (0);
}
