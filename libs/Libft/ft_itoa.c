/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 00:11:07 by sanhan            #+#    #+#             */
/*   Updated: 2020/03/02 00:42:03 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_size(long long n)
{
	int size;

	size = 1;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	int			size;
	long long	temp;
	char		*rtn;
	int			i;

	size = cal_size(n);
	temp = n;
	rtn = (char *)malloc(sizeof(char) * (size + 1));
	if (rtn == 0)
		return (0);
	i = 0;
	if (temp < 0)
	{
		rtn[i] = '-';
		temp *= -1;
		i++;
	}
	rtn[size] = '\0';
	while (--size >= i)
	{
		rtn[size] = (temp % 10) + '0';
		temp /= 10;
	}
	return (rtn);
}
