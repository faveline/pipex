/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:46:52 by faveline          #+#    #+#             */
/*   Updated: 2023/10/19 16:22:25 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_alt;
	const char	*src_alt;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_alt = dest;
	src_alt = src;
	if (src_alt > dest_alt)
	{
		while (n--)
			*(dest_alt++) = *(src_alt++);
	}
	else
	{
		while (n--)
			*(dest_alt + n) = *(src_alt + n);
	}
	return (dest);
}
