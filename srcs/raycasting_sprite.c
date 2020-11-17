/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:57:38 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:52:39 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprites(t_info *info)
{
	int			i;
	int			j;
	int			max;
	t_sprite	temp;

	i = 0;
	max = 0;
	while (i < info->cub->sprite_count - 1)
	{
		max = i;
		j = i + 1;
		while (j < info->cub->sprite_count)
		{
			if (info->sprite[j].distance > info->sprite[i].distance)
				max = j;
			j++;
		}
		if (i != max)
		{
			temp = info->sprite[i];
			info->sprite[i] = info->sprite[max];
			info->sprite[max] = temp;
		}
		i++;
	}
}

void	init_ray_sprite(t_info *info, t_sprite_casting *rs, int i)
{
	rs->sprite_x = info->sprite[i].x - info->pos_x;
	rs->sprite_y = info->sprite[i].y - info->pos_y;
	rs->inv_det = 1.0 /
		((info->plane_x * info->dir_y) - (info->dir_x * info->plane_y));
	rs->transform_x = rs->inv_det
		* ((info->dir_y * rs->sprite_x) - (info->dir_x * rs->sprite_y));
	rs->transform_y = rs->inv_det
		* ((-info->plane_y * rs->sprite_x) + (info->plane_x * rs->sprite_y));
	rs->sprite_screen_x = (int)((info->cub->render_size_x / 2)
								* (1 + rs->transform_x / rs->transform_y));
	rs->sprite_height =
		abs((int)(info->cub->render_size_y / (rs->transform_y)));
	rs->sprite_width = abs((int)(info->cub->render_size_y / (rs->transform_y)));
	rs->draw_start_y = -rs->sprite_height / 2 + info->cub->render_size_y / 2;
	if (rs->draw_start_y < 0)
		rs->draw_start_y = 0;
	rs->draw_end_y = rs->sprite_height / 2 + info->cub->render_size_y / 2;
	if (rs->draw_end_y >= info->cub->render_size_y)
		rs->draw_end_y = info->cub->render_size_y - 1;
	rs->draw_start_x = -rs->sprite_width / 2 + rs->sprite_screen_x;
	if (rs->draw_start_x < 0)
		rs->draw_start_x = 0;
	rs->draw_end_x = rs->sprite_width / 2 + rs->sprite_screen_x;
	if (rs->draw_end_x >= info->cub->render_size_x)
		rs->draw_end_x = info->cub->render_size_x - 1;
}

void	draw_spr_tex(t_info *info, t_sprite_casting *rs, int count)
{
	int	tex_x;
	int	tex_y;
	int	y;
	int	d;
	int	color;

	tex_x = (int)(256 * (count - (-rs->sprite_width / 2 + rs->sprite_screen_x))
			* info->texture_size[4].x / rs->sprite_width) / 256;
	if (rs->transform_y > 0
		&& count > 0
		&& count < info->cub->render_size_x
		&& rs->transform_y < info->z_buffer[count])
	{
		y = rs->draw_start_y;
		while (y < rs->draw_end_y)
		{
			d = (y) * 256 - info->cub->render_size_y * 128
					+ rs->sprite_height * 128;
			tex_y = ((d * 64) / rs->sprite_height) / 256;
			color = info->texture[4][64 * tex_y + tex_x];
			if ((color & 0x00FFFFFF) != 0)
				info->buf[y][count] = color;
			y++;
		}
	}
}

void	draw_sprite(t_info *info, int i)
{
	t_sprite_casting	*rs;
	int					count;

	if (!(rs = (t_sprite_casting *)malloc(sizeof(t_sprite_casting))))
		error_exit("Memory allocation failed");
	init_ray_sprite(info, rs, i);
	count = rs->draw_start_x;
	while (count < rs->draw_end_x)
	{
		draw_spr_tex(info, rs, count);
		count++;
	}
	free(rs);
}
