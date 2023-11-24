/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns_dec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:45:38 by faveline          #+#    #+#             */
/*   Updated: 2023/11/01 17:46:02 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_uns(unsigned int n)
{
	if (n / 10)
		ft_putnbr_uns(n / 10);
	n = n % 10 + 48;
	write(1, &n, 1);
}

int	ft_printf_uns_dec(va_list to_write)
{
	unsigned int	nbr;
	int				i;

	nbr = va_arg(to_write, unsigned int);
	ft_putnbr_uns(nbr);
	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}
