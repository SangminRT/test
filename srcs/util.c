/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 04:33:21 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:22:20 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	floor_ceiling_to_buffer(t_info *info, int x)
{
	int				y;

	y = 0;
	while (y < info->cub->render_size_y / 2)
	{
		info->buf[y][x] = info->cub->ceiling_color;
		y++;
	}
	y = info->cub->render_size_y / 2;
	while (y < info->cub->render_size_y)
	{
		info->buf[y][x] = info->cub->floor_color;
		y++;
	}
}

void	free_two_dimension_array(char **ptr)
{
	int		i;

	i = 0;
	while (*(ptr + i))
		free(*(ptr + i++));
	free(ptr);
}

int		screen_exit(void)
{
	exit(0);
}

void	init_vector(t_pos *to, int x, int y)
{
	to->x = x;
	to->y = y;
}
