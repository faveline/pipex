/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:41:14 by faveline          #+#    #+#             */
/*   Updated: 2023/10/21 17:31:30 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*save;
	void	*test;

	if (!lst || !f || !del)
		return (NULL);
	save = 0;
	while (lst)
	{
		test = f(lst->content);
		new_list = ft_lstnew(test);
		if (new_list == NULL)
		{
			ft_lstclear(&save, del);
			del(test);
			return (NULL);
		}
		ft_lstadd_back(&save, new_list);
		lst = lst->next;
	}
	return (save);
}
