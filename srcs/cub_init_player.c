/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 04:59:25 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:27:45 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cub_set_player_n(t_info *info)
{
	info->dir_x = -1;
	info->dir_y = 0;
	info->plane_x = 0;
	info->plane_y = 0.66;
}

void	cub_set_player_e(t_info *info)
{
	info->dir_x = 0;
	info->dir_y = -1;
	info->plane_x = -0.66;
	info->plane_y = 0;
}

void	cub_set_player_w(t_info *info)
{
	info->dir_x = 0;
	info->dir_y = 1;
	info->plane_x = 0.66;
	info->plane_y = 0;
}

void	cub_set_player_s(t_info *info)
{
	info->dir_x = 1;
	info->dir_y = 0;
	info->plane_x = 0;
	info->plane_y = -0.66;
}

void	cub_set_player(t_info *info, char pos, int i, int j)
{
	info->pos_x = i + 0.5;
	info->pos_y = j + 0.5;
	if (pos == 'N')
		cub_set_player_n(info);
	if (pos == 'E')
		cub_set_player_e(info);
	if (pos == 'W')
		cub_set_player_w(info);
	if (pos == 'S')
		cub_set_player_s(info);
}
