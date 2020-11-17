/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:14:08 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 16:33:51 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line_bonus.h"

void	store_remains_line(t_store *file_fd, int i)
{
	char *temp;

	temp = ft_gstrdup(file_fd->line + i + 1);
	free(file_fd->line);
	(file_fd->line) = ft_gstrdup(temp);
	free(temp);
	temp = 0;
}

int		check_file_line(int fd, char **line, t_store *file_fd)
{
	int	i;

	i = 0;
	file_fd->size = ft_gstrlen(file_fd->line);
	while (i < file_fd->size)
	{
		if ((file_fd->line)[i] == '\n')
		{
			(file_fd->line)[i] = '\0';
			*line = ft_gstrdup(file_fd->line);
			if ((file_fd->line)[i + 1] != '\0')
				store_remains_line(file_fd, i);
			else
			{
				free(file_fd->line);
				file_fd->line = 0;
			}
			return (1);
		}
		i++;
	}
	if (i == file_fd->size)
		return (play_read(fd, line, file_fd));
	return (check_file_line(fd, line, file_fd));
}

int		play_read(int fd, char **line, t_store *file_fd)
{
	int		read_len;
	char	buf[BUFFER_SIZE + 1];

	if ((read_len = read(fd, buf, BUFFER_SIZE)) == -1)
		return (-1);
	buf[read_len] = '\0';
	if (read_len == 0)
	{
		*line = ft_gstrdup(file_fd->line);
		free(file_fd->line);
		file_fd->line = 0;
		return (0);
	}
	file_fd->line = ft_gstrjoin(file_fd->line, buf);
	return (check_file_line(fd, line, file_fd));
}

int		get_next_line(int fd, char **line)
{
	static	t_store file[FDS + 1];
	int				i;

	i = 0;
	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (file[fd].line == 0)
		file[fd].line = ft_zalloc();
	if (ft_gstrlen(file[fd].line) == 0)
		return (play_read(fd, line, &(file[fd])));
	return (check_file_line(fd, line, &(file[fd])));
}
