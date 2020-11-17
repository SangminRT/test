/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:14:53 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 16:36:03 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line_bonus.h"

char	*ft_gstrjoin(char *s1, char const *s2)
{
	char			*rtn;
	unsigned int	s1_len;
	unsigned int	len;
	unsigned int	i;

	s1_len = ft_gstrlen(s1);
	len = s1_len + ft_gstrlen(s2);
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
	free(s1);
	return (rtn);
}

int		ft_gstrlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_gstrdup(char *str)
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

char	*ft_zalloc(void)
{
	char	*rtn;

	if ((rtn = (char *)malloc(1)) == 0)
		return (0);
	rtn[0] = '\0';
	return (rtn);
}
