/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 04:36:34 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/23 08:50:56 by sanhan           ###   ########.fr       */
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

#if 0
void	set_header(unsigned char *header, t_info *info, int imgsize)
{
	unsigned short	bitcount;
	unsigned int	filesize;
	unsigned int	bi_size;
	unsigned int	bf_off_bits;
	unsigned short	bi_planes;

	bi_size = 40;
	bf_off_bits = 54;
	bi_planes = 1;
	bitcount = 24;
	filesize = 54 + imgsize;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 10, &bf_off_bits, 4);
	ft_memcpy(header + 14, &bi_size, 4);
	ft_memcpy(header + 26, &bi_planes, 2);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 18, &info->cub->render_size_x, 4);
	ft_memcpy(header + 22, &info->cub->render_size_y, 4);
	ft_memcpy(header + 28, &bitcount, 2);
	ft_memcpy(header + 34, &imgsize, 4);
}

void	set_pixels(unsigned char *buf, t_info *info, unsigned int wid_bytes)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	tmp = info->cub->render_size_y;
	while (++i < info->cub->render_size_y)
	{
		j = -1;
		--tmp;
		while (++j < info->cub->render_size_x)
		{
			buf[tmp * wid_bytes + j * 3 + 0] = (info->cub->map[i][j]) & 0xff;
			buf[tmp * wid_bytes + j * 3 + 1] = (info->cub->map[i][j] >> 8) & 0xff;
			buf[tmp * wid_bytes + j * 3 + 2] = (info->cub->map[i][j] >> 16) & 0xff;
		}
	}
}

void	make_bmp(unsigned char *header, unsigned char *buf,
					unsigned int size)
{
	int fd;

	fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	write(fd, header, 54);
	write(fd, buf, size);
	close(fd);
}

void	save_bmp(t_info *info)
{
	unsigned char	header[54];
	unsigned char	*buf;
	unsigned int	wid_bytes;
	unsigned int	imgsize;

	wid_bytes = info->cub->render_size_x * 3;
	imgsize = wid_bytes * info->cub->render_size_y;
	set_header(header, info, imgsize);
	buf = malloc(imgsize);
	set_pixels(buf, info, wid_bytes);
	make_bmp(header, buf, imgsize);
	free(buf);
}

#endif

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
