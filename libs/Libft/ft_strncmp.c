/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:11:15 by sanhan            #+#    #+#             */
/*   Updated: 2020/03/05 14:02:36 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	f_len;
	size_t	s_len;
	size_t	i;

	f_len = ft_strlen(s1) + 1;
	s_len = ft_strlen(s2) + 1;
	i = 0;
	if (f_len < n)
		n = f_len;
	if (s_len < n)
		n = s_len;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}
