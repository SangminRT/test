/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:51:52 by sanhan            #+#    #+#             */
/*   Updated: 2020/03/02 14:46:56 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_len(long long temp)
{
	int i;

	i = 0;
	while (temp >= 10)
	{
		temp /= 10;
		i++;
	}
	return (i);
}

static char	div_res(long long temp, int i)
{
	while (i > 0)
	{
		temp /= 10;
		i--;
	}
	temp = temp % 10 + '0';
	return (temp);
}

void		ft_putnbr_fd(int n, int fd)
{
	long long	temp;
	char		rtn;
	int			i;

	temp = n;
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp *= -1;
	}
	i = cal_len(temp);
	while (i >= 0)
	{
		rtn = div_res(temp, i);
		write(fd, &rtn, 1);
		i--;
	}
}
