/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 02:52:34 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 16:13:29 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_pre_validity(t_info *info, int i, int j)
{
	if (!(ft_strchr("NEWS 012", (char)info->cub->map[i][j])))
		error_exit("Contains invalid char.");
	else if (ft_strchr("NEWS", (char)info->cub->map[i][j]))
	{
		if (info->cub->player_check == 1)
			error_exit("Invalid .cub file; check player pos.");
		info->cub->player_check = 1;
		cub_set_player(info, (char)info->cub->map[i][j], i, j);
		info->cub->map[i][j] = '0';
	}
	if (info->cub->map[i][j] == '2')
		info->cub->sprite_count++;
}

void	cub_save_sprite(t_info *info)
{
	int		i;
	int		j;
	int		sprite_count;

	if (!(info->sprite =
		(t_sprite *)malloc(sizeof(t_sprite) * info->cub->sprite_count)))
		error_exit("Memory allocation failed");
	sprite_count = 0;
	i = 0;
	while (i < info->cub->map_row)
	{
		j = 0;
		while (info->cub->map[i][j])
		{
			if (info->cub->map[i][j] == '2')
			{
				info->sprite[sprite_count].x = i + 0.5;
				info->sprite[sprite_count].y = j + 0.5;
				info->cub->map[i][j] = '0';
				sprite_count++;
			}
			j++;
		}
		i++;
	}
}

void	cub_map_checkout(t_info *info)
{
	int		i;
	int		j;

	i = 0;
	while (i < info->cub->map_row)
	{
		j = 0;
		while (info->cub->map[i][j])
		{
			map_pre_validity(info, i, j);
			j++;
		}
		i++;
	}
	if (!info->cub->player_check)
		error_exit("Invalid .cub file; player pos. n/a");
}

int		map_count_end_space(char *s)
{
	int	i;
	int	output;

	i = ft_strlen(s) - 1;
	output = 0;
	while (i != 0)
	{
		if (ft_strchr("NEWS012", s[i]))
			return (output);
		output++;
		i--;
	}
	return (output);
}

void	cub_parse_map(t_cub *cub, char **line, int line_count)
{
	int	i;
	int len;

	if (!(cub->map = (char **)malloc(sizeof(char *) * line_count)))
		error_exit("Memory allocation failed");
	i = 0;
	while (line[i])
	{
		len = (int)ft_strlen(line[i]) - map_count_end_space(line[i]) + 1;
		if (!(cub->map[i] = (char *)malloc(sizeof(char) * (len + 1))))
			error_exit("Memory allocation failed");
		ft_strlcpy(cub->map[i], line[i], len);
		i++;
	}
}
