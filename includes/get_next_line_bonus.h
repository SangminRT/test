/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:51:16 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 16:35:26 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define FDS 500
# define BUFFER_SIZE 1

# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef	struct	s_store
{
	char	*line;
	int		size;
}				t_store;

int				get_next_line(int fd, char **line);
int				ft_gstrlen(const char *s);
int				check_file_line(int fd, char **line, t_store *file_fd);
int				play_read(int fd, char **line, t_store *file_fd);
char			*ft_gstrjoin(char *s1, char const *s2);
char			*ft_gstrdup(char *str);
char			*ft_zalloc(void);
#endif
