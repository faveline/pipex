/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:04:58 by faveline          #+#    #+#             */
/*   Updated: 2023/10/25 11:21:45 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strlen_bis(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_short(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	size_t	j;
	size_t	size;

	j = 0;
	size = 0;
	i = start;
	if (!s)
		return (NULL);
	if (ft_strlen_bis(s) < start)
		return (ft_short());
	while (s[i++] && size < len)
		size++;
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = start;
	while (j < size)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}
