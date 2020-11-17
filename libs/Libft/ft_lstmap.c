/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:54:03 by sanhan            #+#    #+#             */
/*   Updated: 2020/04/13 12:23:46 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtn;
	t_list	*temp;

	rtn = 0;
	while (lst != 0)
	{
		temp = lst;
		ft_lstadd_back(&rtn, ft_lstnew(f(temp->content)));
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (rtn);
}
