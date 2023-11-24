/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:50:47 by faveline          #+#    #+#             */
/*   Updated: 2023/10/19 09:30:41 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	i_c;

	i = 0;
	i_c = -1;
	while (c > 127)
		c -= 128;
	if (c == 0)
	{
		while (s[i])
			i++;
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == c)
			i_c = i;
		i++;
	}
	if (i_c == -1)
		return (NULL);
	return ((char *)&s[i_c]);
}
