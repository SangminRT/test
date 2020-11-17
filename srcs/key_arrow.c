/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_arrow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 05:22:24 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:42:40 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		update_left(t_info *info, double old_dir_x, double old_p_x)
{
	info->dir_x = info->dir_x * cos(info->rot_speed)
					- info->dir_y * sin(info->rot_speed);
	info->dir_y = old_dir_x * sin(info->rot_speed)
					+ info->dir_y * cos(info->rot_speed);
	info->plane_x = info->plane_x * cos(info->rot_speed)
					- info->plane_y * sin(info->rot_speed);
	info->plane_y = old_p_x * sin(info->rot_speed)
					+ info->plane_y * cos(info->rot_speed);
}

void		update_right(t_info *info, double old_dir_x, double old_plane_x)
{
	info->dir_x = info->dir_x * cos(-info->rot_speed)
					- info->dir_y * sin(-info->rot_speed);
	info->dir_y = old_dir_x * sin(-info->rot_speed)
					+ info->dir_y * cos(-info->rot_speed);
	info->plane_x = info->plane_x * cos(-info->rot_speed)
					- info->plane_y * sin(-info->rot_speed);
	info->plane_y = old_plane_x * sin(-info->rot_speed)
					+ info->plane_y * cos(-info->rot_speed);
}

void		move_player_arrow(t_info *info, int key_num)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->dir_x;
	old_plane_x = info->plane_x;
	if (key_num == KEY_LEFT)
		update_left(info, old_dir_x, old_plane_x);
	else if (key_num == KEY_RIGHT)
		update_right(info, old_dir_x, old_plane_x);
}
