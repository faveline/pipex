/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:06:52 by faveline          #+#    #+#             */
/*   Updated: 2023/11/02 11:44:34 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_search_type(const char stri, va_list to_write)
{
	int	error;

	error = 0;
	if (stri == 'c')
		error = ft_printf_char(to_write);
	else if (stri == 's')
		error = ft_printf_string(to_write);
	else if (stri == 'p')
		error = ft_printf_point(to_write);
	else if (stri == 'd')
		error = ft_printf_decimal(to_write);
	else if (stri == 'i')
		error = ft_printf_int(to_write);
	else if (stri == 'u')
		error = ft_printf_uns_dec(to_write);
	else if (stri == 'x')
		error = ft_printf_hexa_lower(to_write);
	else if (stri == 'X')
		error = ft_printf_hexa_upper(to_write);
	else if (stri == '%')
		error = write(1, "%", 1);
	return (error);
}

static int	ft_check_str(const char stri)
{
	if (stri != 'c' && stri != 's' && stri != 'p' && stri != 'd'
		&& stri != 'i' && stri != 'u' && stri != 'x'
		&& stri != 'X' && stri != '%')
		return (-1);
	return (0);
}

static int	ft_boucle(va_list to_write, const char *str, int error, int i)
{
	int	cpt;

	cpt = 0;
	while (str[i])
	{
		if (str[i] != '%' || (str[i] == '%' && ft_check_str(str[i + 1]) == -1))
		{
			write(1, &str[i], 1);
			cpt++;
		}
		else
		{
			i++;
			error = ft_search_type(str[i], to_write);
			if (error < 0)
				return (error);
			cpt += error;
		}
		i++;
	}
	return (cpt);
}

int	ft_printf(const char *str, ...)
{
	va_list	to_write;
	int		cpt;

	va_start(to_write, str);
	cpt = ft_boucle(to_write, str, 0, 0);
	va_end(to_write);
	return (cpt);
}
