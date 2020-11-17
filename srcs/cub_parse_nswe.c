/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_nswe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 02:33:38 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:27:11 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	setup_no_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->no_path) > 0)
		error_exit("Invalid .cub file; 'NO' already given\n");
	cub->no_path = ft_strdup(path);
}

void	setup_so_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->so_path) > 0)
		error_exit("Invalid .cub file; 'SO' already given\n");
	cub->so_path = ft_strdup(path);
}

void	setup_we_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->we_path) > 0)
		error_exit("Invalid .cub file; 'WE' already given\n");
	cub->we_path = ft_strdup(path);
}

void	setup_ea_path(t_cub *cub, char *path)
{
	if (ft_strlen(cub->ea_path) > 0)
		error_exit("Invalid .cub file; 'EA' already given\n");
	cub->ea_path = ft_strdup(path);
}

void	cub_parse_nswe(t_cub *cub, char **temp)
{
	if (!ft_strchr("NEWSFCR", (char)temp[0][0]))
		error_exit("Invalid .cub file\n");
	check_valid_file(temp[1]);
	if ((char)temp[0][0] == 'N' && (char)temp[0][1] == 'O')
		setup_no_path(cub, temp[1]);
	else if ((char)temp[0][0] == 'S' && (char)temp[0][1] == 'O')
		setup_so_path(cub, temp[1]);
	else if ((char)temp[0][0] == 'W' && (char)temp[0][1] == 'E')
		setup_we_path(cub, temp[1]);
	else if ((char)temp[0][0] == 'E' && (char)temp[0][1] == 'A')
		setup_ea_path(cub, temp[1]);
	else
		error_exit("Invalid .cub file;  Check image path\n");
}
