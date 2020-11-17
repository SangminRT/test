/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:29:58 by sanhan            #+#    #+#             */
/*   Updated: 2020/03/02 00:04:58 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_size(char *s, char c)
{
	int i;
	int rtn;
	int s_len;

	i = 0;
	rtn = 0;
	s_len = ft_strlen(s);
	while (i < s_len)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			rtn++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (rtn);
}

static int	cal_len(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	all_free(char **rtn, int until)
{
	int i;

	i = 0;
	while (i < until)
	{
		free(rtn[i]);
		i++;
	}
	free(rtn);
}

static void	allocation(char *s, char c, char **rtn, int size)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j] && s[j] != c)
		{
			rtn[i] = (char *)malloc(sizeof(char) * (cal_len(&s[j], c) + 1));
			if (rtn[i] == 0)
			{
				all_free(rtn, i);
				return ;
			}
		}
		k = 0;
		while (s[j] && s[j] != c)
			rtn[i][k++] = s[j++];
		rtn[i++][k] = '\0';
	}
	rtn[i] = 0;
}

char		**ft_split(char const *s, char c)
{
	int		size;
	char	**rtn;

	size = cal_size((char *)s, c);
	rtn = (char **)malloc(sizeof(char *) * (size + 1));
	if (rtn == 0)
		return (0);
	allocation((char *)s, c, rtn, size);
	return (rtn);
}
