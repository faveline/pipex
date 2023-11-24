/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:45:45 by faveline          #+#    #+#             */
/*   Updated: 2023/10/19 09:42:57 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	if (i == size)
	{
		while (src[j])
			j++;
		return (j + size);
	}
	while (src[j] && i < size - 1)
		dst[i++] = src[j++];
	dst[i] = 0;
	while (src[j])
	{
		i++;
		j++;
	}
	return (i);
}
