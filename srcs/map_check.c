/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:15:37 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:23:37 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			set_top_bot_space(t_info *info, char **max_pad)
{
	int			j;

	j = 0;
	while (j < info->cub->map_col + 2)
	{
		max_pad[0][j] = ' ';
		max_pad[info->cub->map_row + 1][j] = ' ';
		j++;
	}
	max_pad[0][j] = '\0';
	max_pad[info->cub->map_row + 1][j] = '\0';
}

void			fill_rest(t_info *info, char **max_pad)
{
	int			i;
	int			j;

	i = 0;
	while ((i + 1) < (info->cub->map_row + 1))
	{
		j = 0;
		max_pad[(i + 1)][j] = ' ';
		while ((j + 1) < (info->cub->map_col + 3))
		{
			if (j < (int)ft_strlen(info->cub->map[i]))
				max_pad[(i + 1)][(j + 1)] = info->cub->map[i][j];
			else
				max_pad[(i + 1)][(j + 1)] = ' ';
			j++;
		}
		max_pad[(i + 1)][j] = '\0';
		i++;
	}
}

int				is_valid_map(t_info *info, int x, int y, int *visited)
{
	int			i;
	int			*dx;
	int			*dy;
	t_pos		to;

	if (x <= 0 || x >= info->cub->map_row + 1
		|| y <= 0 || y >= info->cub->map_col + 2)
		return (0);
	visited[y * (info->cub->map_row + 2) + x] = 1;
	dx = (int[4]){1, -1, 0, 0};
	dy = (int[4]){0, 0, -1, 1};
	if (info->max_pad[x][y] == ' ')
		return (0);
	i = 0;
	while (i < 4)
	{
		init_vector(&to, x + dx[i], y + dy[i]);
		if (0 <= to.x && to.x < info->cub->map_row + 2 && 0 <= to.y &&
		to.y < info->cub->map_col + 3 && info->max_pad[to.x][to.y] != '1' &&
			!visited[to.y * (info->cub->map_row + 2) + to.x])
			if (!is_valid_map(info, to.x, to.y, visited))
				return (0);
		i++;
	}
	return (1);
}

char			**create_padded_square(t_info *info)
{
	char		**max_pad;
	int			i;

	if (!(max_pad =
		(char **)malloc(sizeof(char *) * (info->cub->map_row + 2))))
		error_exit("Memory allocation failed");
	i = -1;
	while (++i < info->cub->map_row + 2)
	{
		if (!(max_pad[i] =
			(char *)malloc(sizeof(char) * (info->cub->map_col + 3))))
			error_exit("Memory allocation failed");
	}
	set_top_bot_space(info, max_pad);
	fill_rest(info, max_pad);
	return (max_pad);
}

void			check_map_valid(t_info *info, double pos_x, double pos_y)
{
	int			player_x;
	int			player_y;
	int			i;
	int			*visited;

	if (!(visited = (int *)malloc(sizeof(int) * ((info->cub->map_row + 2)
			* (info->cub->map_col + 3)))))
		error_exit("Memory allocation failed");
	i = 0;
	while (i < (info->cub->map_row + 2) * (info->cub->map_col + 3))
		visited[i++] = 0;
	if (!(info->max_pad = create_padded_square(info)))
		return ;
	player_x = (int)(pos_x);
	player_y = (int)(pos_y);
	if (is_valid_map(info, player_x, player_y, visited) == 0)
		error_exit("Invalid .cub file; Not a valid map");
	free(visited);
	i = 0;
	while (i < info->cub->map_row + 2)
		free(info->max_pad[i++]);
	free(info->max_pad);
}
