/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:03:11 by faveline          #+#    #+#             */
/*   Updated: 2023/10/27 18:16:41 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcat_next(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		size;

	size = 0;
	while (s1[size])
		size++;
	i = 0;
	while (s2[i++])
		size++;
	s = (char *)malloc((size + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	size = 0;
	while (s2[size])
		s[i++] = s2[size++];
	s[i] = 0;
	return (s);
}

char	*ft_cat_free(char *next_line, char *next_line_tmp, int k, int flag)
{
	char	*next_line_tmp2;

	if (flag == 1)
	{
		next_line_tmp[k] = '\n';
		next_line_tmp[k + 1] = 0;
	}
	else
		next_line_tmp[k] = 0;
	next_line_tmp2 = ft_strcat_next(next_line, next_line_tmp);
	free(next_line_tmp);
	if (next_line[0] != 0)
		free(next_line);
	if (next_line_tmp2 == NULL)
		return (NULL);
	next_line = ft_strcat_next("\0", next_line_tmp2);
	free(next_line_tmp2);
	if (next_line == NULL)
		return (NULL);
	return (next_line);
}

void	ft_modif_buff(char *buff, int SIZE)
{
	int	i;
	int	j;

	i = 0;
	while (buff[i] != '\n' && buff[i])
		i++;
	if (!buff[i])
	{
		buff[0] = 0;
		return ;
	}
	i++;
	j = 0;
	while (i < SIZE)
		buff[j++] = buff[i++];
	while (j < SIZE)
		buff[j++] = '\0';
}
