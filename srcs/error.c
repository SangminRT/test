/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 02:46:02 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 15:45:18 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(1, "Error\n", 6);
	write(1, msg, len);
	exit(1);
}

void	check_valid_file(char *filepath)
{
	int	fd;

	if ((fd = open(filepath, O_RDONLY)) != 3)
	{
		perror(ft_strjoin("Error\n", filepath));
		exit(1);
	}
	close(fd);
}
