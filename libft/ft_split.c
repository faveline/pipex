/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:45:20 by faveline          #+#    #+#             */
/*   Updated: 2023/10/25 11:17:18 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		i++;
		size++;
	}
	return (size);
}

static void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**ft_crea_tab(char **tab, char const *s, char c, int i)
{
	int	j;
	int	k;
	int	size;

	k = 0;
	while (s[i])
	{
		size = ft_size_word(s, c, i);
		tab[k] = (char *)malloc((size + 1) * sizeof(char));
		if (tab[k] == NULL)
		{
			ft_free(tab);
			return (NULL);
		}
		j = 0;
		while (j < size)
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		while (s[i] == c && s[i])
			i++;
		k++;
	}
	return (tab);
}

static int	ft_nb_word(char const *s, char c, int i)
{
	int	nb;

	nb = 0;
	if (c == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			nb++;
		i++;
	}
	if (s[i - 1] != c)
		nb++;
	if (nb == 0)
		return (1);
	return (nb);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	if (!s[i])
	{
		tab = (char **)malloc(sizeof(char *));
		if (tab == NULL)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tab = (char **)malloc((ft_nb_word(s, c, i) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = ft_crea_tab(tab, s, c, i);
	if (tab == NULL)
		return (NULL);
	tab[ft_nb_word(s, c, i)] = NULL;
	return (tab);
}
