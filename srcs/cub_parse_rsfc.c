/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_rsfc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 04:52:47 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 12:51:32 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		cub_parse_f(t_cub *cub, char **color)
{
	int		i;
	int		j;

	i = 0;
	while (color[i])
		i++;
	if (i != 3)
		error_exit("Invalid .cub file; Given color not valid");
	if (cub->floor_color)
		error_exit("Invalid .cub file; check if fields are given");
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			error_exit("Invalid .cub file; check fllor color");
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j++]))
				error_exit("Invalid .cub file; check floor color");
		}
		cub->floor_color = cub->floor_color * 256 + ft_atoi(color[i++]);
	}
}

void		cub_parse_c(t_cub *cub, char **color)
{
	int		i;
	int		j;

	i = 0;
	while (color[i])
		i++;
	if (i != 3)
		error_exit("Invalid .cub file; Given color not valid");
	if (cub->ceiling_color)
		error_exit("Invalid .cub file; check if fields are given");
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			error_exit("Invalid .cub file; check ceiling color");
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j++]))
				error_exit("Invalid .cub file; check ceiling color");
		}
		cub->ceiling_color = cub->ceiling_color * 256 + ft_atoi(color[i++]);
	}
}

void		cub_parse_res(t_cub *cub, char **temp, int split_count, int c)
{
	int		i;

	i = 0;
	if (split_count != 3)
		error_exit("Invalid .cub file\n");
	else if (c == 'r')
		error_exit("Invalid .cub file\n");
	else if (cub->render_size_x != 0 || cub->render_size_y != 0)
		error_exit("Invalid .cub file\n");
	i = 0;
	while (temp[1][i])
	{
		if (!ft_isdigit(temp[1][i++]))
			error_exit("Invalid .cub file\n");
	}
	i = 0;
	while (temp[2][i])
	{
		if (!ft_isdigit(temp[2][i++]))
			error_exit("Invalid .cub file\n");
	}
	cub->render_size_x = ft_atoi(temp[1]);
	cub->render_size_y = ft_atoi(temp[2]);
}

void		cub_parse_rest(t_cub *cub, char **temp, int split_count)
{
	char	**color_temp;
	int		j;

	j = 0;
	if ((char)temp[0][0] == 'R' || (char)temp[0][0] == 'r')
		cub_parse_res(cub, temp, split_count, (int)temp[0][0]);
	else if ((char)temp[0][0] == 'S')
	{
		if (ft_strlen(cub->sprite_path))
			error_exit("Invalid .cub file; Sprite already given");
		check_valid_file(temp[1]);
		cub->sprite_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'F' || (char)temp[0][0] == 'C')
	{
		color_temp = ft_split(temp[1], ',');
		if ((char)temp[0][0] == 'F')
			cub_parse_f(cub, color_temp);
		else
			cub_parse_c(cub, color_temp);
		free_two_dimension_array(color_temp);
	}
	else
		error_exit("Check .cub file is valid");
}
