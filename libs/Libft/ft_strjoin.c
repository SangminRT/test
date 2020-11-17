/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:53:06 by sanhan            #+#    #+#             */
/*   Updated: 2020/03/07 09:38:13 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*rtn;
	unsigned int	s1_len;
	unsigned int	len;
	unsigned int	i;

	s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2);
	rtn = (char *)malloc(sizeof(char) * (len + 1));
	if (rtn == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		rtn[i] = s1[i];
		i++;
	}
	while (s2[i - s1_len])
	{
		rtn[i] = s2[i - s1_len];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
