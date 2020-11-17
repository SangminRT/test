/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:00:36 by sanhan            #+#    #+#             */
/*   Updated: 2020/02/28 15:59:44 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(src);
	while (dst[i] && i < dstsize)
		i++;
	while (*src && i + 1 < dstsize)
	{
		dst[i] = *src++;
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (*src)
	{
		i++;
		src++;
	}
	return (i);
}
