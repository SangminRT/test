/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:54:19 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:40:54 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_step_and_side(t_info *info, t_wall_casting *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (info->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - info->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (info->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - info->pos_y) * ray->delta_dist_y;
	}
}

void	find_and_calc_wall(t_info *info, t_wall_casting *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (info->cub->map[ray->map_x][ray->map_y] == '1')
			hit = 1;
	}
	ray->perp_wall_dist = (ray->side == 0)
		? ((ray->map_x - info->pos_x) + (1 - ray->step_x) / 2) / ray->ray_dir_x
		: ((ray->map_y - info->pos_y) + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	calculate_wall_texture(t_info *info, t_wall_casting *ray)
{
	ray->line_height = (int)(info->cub->render_size_y / ray->perp_wall_dist);
	if ((ray->draw_start =
		-ray->line_height / 2 + info->cub->render_size_y / 2) < 0)
		ray->draw_start = 0;
	if ((ray->draw_end = ray->line_height / 2 + info->cub->render_size_y / 2)
		>= info->cub->render_size_y)
		ray->draw_end = info->cub->render_size_y - 1;
	if (ray->side == 0)
	{
		ray->tex_num = (ray->ray_dir_x > 0) ? 1 : 0;
		ray->wall_x = info->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->tex_num = (ray->ray_dir_y < 0) ? 3 : 2;
		ray->wall_x = info->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x =
		(int)(ray->wall_x * (double)info->texture_size[ray->tex_num].x);
	if ((ray->side == 0 && ray->ray_dir_x > 0) \
			|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = info->texture_size[ray->tex_num].x - ray->tex_x - 1;
}

void	init_ray(int x, t_info *info, t_wall_casting *ray)
{
	ray->camera_x = 2 * x / (double)info->cub->render_size_x - 1;
	ray->ray_dir_x = info->dir_x + info->plane_x * ray->camera_x;
	ray->ray_dir_y = info->dir_y + info->plane_y * ray->camera_x;
	ray->map_x = (int)info->pos_x;
	ray->map_y = (int)info->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	set_step_and_side(info, ray);
	find_and_calc_wall(info, ray);
	calculate_wall_texture(info, ray);
}

void	wall_to_buffer(t_info *info, int x)
{
	t_wall_casting	*ray;
	double			s;
	double			tex_pos;
	int				color;
	int				y;

	if (!(ray = (t_wall_casting *)malloc(sizeof(t_wall_casting))))
		return ;
	init_ray(x, info, ray);
	s = info->texture_size[ray->tex_num].y * 1.0 / ray->line_height;
	tex_pos =
	(ray->draw_start - info->cub->render_size_y / 2 + ray->line_height / 2) * s;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)tex_pos & (info->texture_size[ray->tex_num].y - 1);
		tex_pos += s;
		color = info->texture[ray->tex_num][
				info->texture_size[ray->tex_num].y * ray->tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y++][x] = color;
	}
	info->z_buffer[x] = ray->perp_wall_dist;
	free(ray);
}
