/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:08:15 by faveline          #+#    #+#             */
/*   Updated: 2023/11/14 14:34:31 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int		ft_printf(const char *str, ...);
int		ft_printf_char(va_list to_write);
int		ft_printf_string(va_list to_write);
int		ft_printf_point(va_list to_write);
int		ft_printf_decimal(va_list to_write);
int		ft_printf_int(va_list to_write);
int		ft_printf_uns_dec(va_list to_write);
int		ft_printf_hexa_lower(va_list to_write);
int		ft_printf_hexa_upper(va_list to_write);

#endif
