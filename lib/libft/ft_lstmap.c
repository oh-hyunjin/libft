/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:27:44 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/18 11:44:09 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cur;

	new = NULL;
	while (lst != NULL)
	{
		cur = ft_lstnew(f(lst->content));
		if (cur == 0)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, cur);
		cur = cur->next;
		lst = lst->next;
	}
	return (new);
}
