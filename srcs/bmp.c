/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 04:36:34 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 04:44:31 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void					set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void					write_bmp_header(t_info *info, int fd, int size)
{
	unsigned char		header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, info->cub->render_size_x);
	set_int_in_char(header + 22, info->cub->render_size_y);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void					write_data(t_info *info, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = info->cub->render_size_y - 1;
	pad = (4 - (info->cub->render_size_x * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < info->cub->render_size_x)
		{
			write(fd, &(info->buf[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

int						save_bmp(t_info *info)
{
	int					fd;
	int					size;

	size = 54 + 3 * info->cub->render_size_x * info->cub->render_size_y;
	if ((fd = open("./screenshot.bmp", O_WRONLY | O_CREAT |
						O_TRUNC | O_APPEND, 00755)) < 0)
		return (0);
	write_bmp_header(info, fd, size);
	write_data(info, fd);
	return (1);
}

void					bmp_main(t_info *info, char *path)
{
	init_info(info, path);
	init_info_rest(info);
	calc(info);
	draw(info);
	save_bmp(info);
	exit(0);
}
