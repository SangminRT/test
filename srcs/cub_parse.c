/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 02:00:40 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:44:09 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cub_parse_element(t_cub *cub, char **cub_temp)
{
	char	**temp;
	int		i;
	int		split_count;

	i = 0;
	while (i < 8)
	{
		temp = ft_split(cub_temp[i], ' ');
		split_count = 0;
		while (temp[split_count])
			split_count++;
		if (2 > split_count || split_count > 3 || ft_isalpha(temp[0][0]) == 0
				|| (split_count == 3 &&
					((char)temp[0][0] != 'R' || ft_strlen(temp[0]) > 1))
				|| (split_count == 2 && ft_strlen(temp[0]) > 2))
			error_exit("Invalid .cub file\n");
		if (ft_strlen(temp[0]) == 2)
			cub_parse_nswe(cub, temp);
		else
			cub_parse_rest(cub, temp, split_count);
		free_two_dimension_array(temp);
		i++;
	}
}

char	*cub_read_line(const char *path)
{
	int		fd;
	char	*temp;
	char	*store;
	char	*line;

	if ((fd = open(path, O_RDONLY)) != 3)
	{
		perror(ft_strjoin("Error\n", path));
		exit(1);
	}
	store = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		temp = ft_strjoin(store, line);
		free(store);
		store = temp;
		temp = ft_strjoin(store, "\n");
		free(store);
		store = temp;
		free(line);
	}
	free(line);
	close(fd);
	return (store);
}

void	cal_max_column(t_cub *cub)
{
	int		i;
	int		m_c;

	m_c = 0;
	i = 0;
	while (i < cub->map_row)
	{
		if (m_c < (int)ft_strlen(cub->map[i]))
		{
			m_c = (int)ft_strlen(cub->map[i]);
		}
		i++;
	}
	cub->map_col = m_c;
}

void	cub_read_file(t_info *info, const char *path)
{
	char	*line;
	char	**cub_temp;
	int		cub_line_num;

	init_cub(info->cub);
	line = cub_read_line(path);
	cub_temp = ft_split(line, '\n');
	cub_line_num = 0;
	while (cub_temp[cub_line_num])
		cub_line_num++;
	info->cub->map_row = cub_line_num - 8;
	cub_parse_element(info->cub, cub_temp);
	cub_parse_map(info->cub, (cub_temp + 8), info->cub->map_row);
	cal_max_column(info->cub);
	cub_map_checkout(info);
	cub_save_sprite(info);
	check_map_valid(info, info->pos_x, info->pos_y);
	free(line);
	free_two_dimension_array(cub_temp);
	cub_temp = NULL;
}
