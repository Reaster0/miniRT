/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:24:27 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/16 17:14:47 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	result = NULL;
	while (lst && f)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp->content)
		{
			ft_lstclear(&result, del);
			return (result);
		}
		ft_lstadd_back(&result, temp);
		lst = lst->next;
	}
	return (result);
}
