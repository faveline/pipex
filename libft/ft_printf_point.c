/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:04:18 by faveline          #+#    #+#             */
/*   Updated: 2023/11/03 10:39:51 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_conv(char *adrs, long unsigned int ptr, int size, char *hexa)
{
	adrs[size + 1] = 0;
	while (size >= 0)
	{
		adrs[size] = hexa[ptr % 16];
		ptr /= 16;
		size--;
	}
	adrs[0] = '0';
	adrs[1] = 'x';
	return (adrs);
}

static int	ft_size_conv(long unsigned int conv, int i)
{
	while (conv != 0)
	{
		conv /= 16;
		i++;
	}
	return (i);
}

int	ft_printf_point(va_list to_write)
{
	void				*ptr;
	long unsigned int	conv;
	char				*adrs;
	int					i;

	ptr = va_arg(to_write, void *);
	if (ptr == 0)
	{
		write(1, "0x0", 3);
		return (3);
	}
	conv = (long unsigned int) ptr;
	i = ft_size_conv(conv, 0);
	adrs = (char *)malloc((i + 3) * sizeof(char));
	if (adrs == NULL)
		return (-1);
	adrs = ft_conv(adrs, conv, i + 1, "0123456789abcdef");
	i = 0;
	while (adrs[i])
		write(1, &adrs[i++], 1);
	free(adrs);
	return (i);
}
