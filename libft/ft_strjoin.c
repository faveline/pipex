/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:24:20 by faveline          #+#    #+#             */
/*   Updated: 2023/10/25 11:24:40 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_size(char const *s1, char const *s2)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (s1[i])
	{
		size++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_size(s1, s2) + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}
