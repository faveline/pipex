/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:09:04 by faveline          #+#    #+#             */
/*   Updated: 2023/10/20 16:35:50 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*ptr2;

	if (!lst || !del)
		return ;
	ptr2 = *lst;
	ptr = *lst;
	while (ptr != NULL)
	{
		ptr2 = ptr2->next;
		ft_lstdelone(ptr, del);
		ptr = ptr2;
	}
	*lst = NULL;
}
