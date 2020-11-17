/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:45:40 by sanhan            #+#    #+#             */
/*   Updated: 2020/04/06 09:12:53 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*rtn;
	int		s_len;
	int		i;

	s_len = ft_strlen(s);
	i = 0;
	rtn = 0;
	while (i <= s_len)
	{
		if (s[i] == (char)c)
			rtn = &((char *)s)[i];
		i++;
	}
	return (rtn);
}
