/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_wsad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:40:59 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:43:19 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_player_w(t_info *info)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(info->pos_x + (info->dir_x * (2 * info->move_speed)));
	fd_pos_y = (int)(info->pos_y + (info->dir_y * (2 * info->move_speed)));
	if (info->cub->map[fd_pos_x][(int)(info->pos_y)] == '0')
		info->pos_x += info->dir_x * info->move_speed;
	if (info->cub->map[(int)(info->pos_x)][fd_pos_y] == '0')
		info->pos_y += info->dir_y * info->move_speed;
}

void	move_player_a(t_info *info)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(info->pos_x - (info->dir_y * (2 * info->move_speed)));
	fd_pos_y = (int)(info->pos_y + (info->dir_x * (2 * info->move_speed)));
	if (info->cub->map[fd_pos_x][(int)(info->pos_y)] == '0')
		info->pos_x += -(info->dir_y * info->move_speed);
	if (info->cub->map[(int)(info->pos_x)][fd_pos_y] == '0')
		info->pos_y += (info->dir_x * info->move_speed);
}

void	move_player_s(t_info *info)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(info->pos_x - (info->dir_x * (2 * info->move_speed)));
	fd_pos_y = (int)(info->pos_y - (info->dir_y * (2 * info->move_speed)));
	if (info->cub->map[fd_pos_x][(int)(info->pos_y)] == '0')
		info->pos_x -= info->dir_x * info->move_speed;
	if (info->cub->map[(int)(info->pos_x)][fd_pos_y] == '0')
		info->pos_y -= info->dir_y * info->move_speed;
}

void	move_player_d(t_info *info)
{
	int	fd_pos_x;
	int	fd_pos_y;

	fd_pos_x = (int)(info->pos_x + (info->dir_y * (2 * info->move_speed)));
	fd_pos_y = (int)(info->pos_y - (info->dir_x * (2 * info->move_speed)));
	if (info->cub->map[fd_pos_x][fd_pos_y] == '0')
		info->pos_x += (info->dir_y * info->move_speed);
	if (info->cub->map[(int)(info->pos_x)][fd_pos_y] == '0')
		info->pos_y += -(info->dir_x * info->move_speed);
}
