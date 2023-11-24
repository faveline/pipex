/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:17:54 by faveline          #+#    #+#             */
/*   Updated: 2023/10/19 16:20:48 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_alt;
	const unsigned char	*src_alt;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_alt = dest;
	src_alt = src;
	while (n--)
		*(dest_alt++) = *(src_alt++);
	return (dest);
}
