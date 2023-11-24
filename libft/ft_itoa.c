/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:51:45 by faveline          #+#    #+#             */
/*   Updated: 2023/10/19 13:42:01 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_size_itoa(int n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_nbr(int n, char *itoa, int size)
{
	itoa[size] = 0;
	if (n == 0)
		itoa[0] = 48;
	while (n > 0)
	{
		itoa[size - 1] = n % 10 + 48;
		size--;
		n /= 10;
	}
	return (itoa);
}

static char	*ft_int_min(void)
{
	char	*itoa;

	itoa = (char *)malloc(12 * sizeof(char));
	if (itoa == NULL)
		return (itoa);
	itoa[0] = '-';
	itoa = ft_nbr(214748364, itoa, 10);
	itoa[10] = 56;
	itoa[11] = '\0';
	return (itoa);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		size;

	if (n == -2147483648)
	{
		itoa = ft_int_min();
		return (itoa);
	}
	else if (n <= 0)
		size = ft_size_itoa(n) + 1;
	else
		size = ft_size_itoa(n);
	itoa = (char *)malloc((size + 1) * sizeof(char));
	if (itoa == NULL)
		return (itoa);
	if (n < 0)
	{
		n *= -1;
		itoa[0] = '-';
		itoa = ft_nbr(n, itoa, size);
	}
	else
		itoa = ft_nbr(n, itoa, size);
	return (itoa);
}
