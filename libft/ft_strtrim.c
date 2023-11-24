/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:41:08 by faveline          #+#    #+#             */
/*   Updated: 2023/10/19 18:20:33 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_first(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (s1[i] && flag == 0)
	{
		j = 0;
		flag = 1;
		while (set[j] && flag == 1)
		{
			if (set[j] == s1[i])
				flag = 0;
			j++;
		}
		i++;
	}
	return (i - 1);
}

static int	ft_last(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (s1[i])
		i++;
	i--;
	flag = 0;
	while (s1[i] && flag == 0)
	{
		flag = 1;
		j = 0;
		while (set[j] && flag == 1)
		{
			if (set[j] == s1[i])
				flag = 0;
			j++;
		}
		i--;
	}
	return (i + 1);
}

static char	*ft_creat_malloc(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (str == NULL)
		return (str);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		last;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_creat_malloc());
	j = 0;
	i = ft_first(s1, set);
	if (!s1[i + 1])
		return (ft_creat_malloc());
	last = ft_last(s1, set);
	str = (char *)malloc(((last - i) + 2) * sizeof(char));
	if (str == NULL)
		return (str);
	while (i <= last)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}
