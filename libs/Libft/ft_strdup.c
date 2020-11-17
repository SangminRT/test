/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:37:26 by sanhan            #+#    #+#             */
/*   Updated: 2020/04/06 09:24:36 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char		*rtn;
	long long	len;

	len = 0;
	while (str[len])
		len++;
	if ((rtn = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	while (*str)
	{
		*rtn = *str;
		rtn++;
		str++;
	}
	*rtn = '\0';
	return (rtn - len);
}
