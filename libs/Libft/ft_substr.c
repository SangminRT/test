/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:02:46 by sanhan            #+#    #+#             */
/*   Updated: 2020/04/25 15:17:51 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rtn;
	unsigned int	s_len;
	unsigned int	i;

	s_len = ft_strlen(s);
	if (s == 0)
		return (0);
	if (start > s_len)
		return (ft_calloc(1, 1));
	if ((s_len - start) < len)
		len = (s_len - start);
	rtn = (char	*)malloc(sizeof(char) * (len + 1));
	if (rtn == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		rtn[i] = s[start + i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
