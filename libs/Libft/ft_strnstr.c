/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:10:15 by sanhan            #+#    #+#             */
/*   Updated: 2020/04/06 09:10:42 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*rtn;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return (&((char *)haystack)[i]);
	if (len == 0)
		return (0);
	if (len > (size_t)ft_strlen(haystack))
		len = ft_strlen(haystack);
	while (i < len && haystack[i] != needle[j])
		i++;
	rtn = &((char *)haystack)[i];
	while (i < len && (haystack[i] == needle[j]) && needle[j])
	{
		i++;
		j++;
	}
	if (needle[j] == '\0')
		return (rtn);
	if ((rtn = ft_strnstr(&haystack[i], needle, (len - i))))
		return (rtn);
	return (0);
}
