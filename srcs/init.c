/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:35:00 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:47:05 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_info *info, int i, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
			&img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->size_l, &img->endian);
	info->texture_size[i].x = img->width;
	info->texture_size[i].y = img->height;
	if (!(info->texture[i] =
		(int *)malloc(sizeof(int) * (img->width * img->height))))
		error_exit("Memory allocation failed");
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			info->texture[i][img->width * y + x] =
				img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	temp;
	int		i;

	if (!(info->texture = (int **)malloc(sizeof(int*) * (TEXTURE_KIND))))
		error_exit("Memory allocation failed");
	if (!(info->texture_size = (t_pos *)malloc(sizeof(t_pos) * (TEXTURE_KIND))))
		error_exit("Memory allocation failed");
	i = 0;
	load_image(info, i++, info->cub->no_path, &temp);
	load_image(info, i++, info->cub->so_path, &temp);
	load_image(info, i++, info->cub->we_path, &temp);
	load_image(info, i++, info->cub->ea_path, &temp);
	load_image(info, i, info->cub->sprite_path, &temp);
}

void	init_cub(t_cub *cub)
{
	cub->render_size_x = 0;
	cub->render_size_y = 0;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->map_row = 0;
	cub->map_col = 0;
	cub->sprite_count = 0;
	cub->no_path = "";
	cub->so_path = "";
	cub->ea_path = "";
	cub->we_path = "";
	cub->sprite_path = "";
	cub->player_check = 0;
}

void	init_info(t_info *info, char *path)
{
	int i;

	i = 0;
	info->mlx = mlx_init();
	if (!(info->cub = (t_cub *)malloc(sizeof(t_cub))))
		error_exit("Memory allocation failed");
	cub_read_file(info, path);
	if (info->cub->render_size_x > SCREENWIDTH
		|| info->cub->render_size_x < 201)
		info->cub->render_size_x = SCREENWIDTH;
	if (info->cub->render_size_y > SCREENHEIGHT
		|| info->cub->render_size_y < 201)
		info->cub->render_size_y = SCREENHEIGHT;
	info->win = mlx_new_window(info->mlx,
		info->cub->render_size_x, info->cub->render_size_y, "cub3D by sanhan");
	if (!(info->buf = (int **)malloc(sizeof(int *) * info->cub->render_size_y)))
		error_exit("Memory allocation failed");
	while (i < info->cub->render_size_y)
	{
		if (!(info->buf[i] =
					(int *)malloc(sizeof(int) * info->cub->render_size_x)))
			error_exit("Memory allocation failed");
		i++;
	}
	load_texture(info);
}

void	init_info_rest(t_info *info)
{
	info->move_speed = 0.05;
	info->rot_speed = 0.05;
	info->img.img = mlx_new_image(info->mlx,
			info->cub->render_size_x, info->cub->render_size_y);
	info->img.data =
		(int *)mlx_get_data_addr(info->img.img, &info->img.bpp,
				&info->img.size_l, &info->img.endian);
	if (!(info->z_buffer =
			(double *)malloc(sizeof(double) * (info->cub->render_size_x))))
		error_exit("Memory allocation failed");
	if (!(info->sprite_order =
			(int *)malloc(sizeof(int) * (info->cub->sprite_count))))
		error_exit("Memory allocation failed");
	if (!(info->sprite_dist =
			(double *)malloc(sizeof(double) * (info->cub->sprite_count))))
		error_exit("Memory allocation failed");
}
