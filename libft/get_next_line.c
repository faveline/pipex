/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:28:30 by faveline          #+#    #+#             */
/*   Updated: 2023/10/29 14:35:31 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_creat_new(char *next_line, char *buff, int flag, int save)
{
	int		k;
	char	*next_line_tmp;

	next_line_tmp = (char *)malloc((save + flag + 1) * sizeof(char));
	if (next_line_tmp == NULL)
		return (NULL);
	k = 0;
	while (k < save)
	{
		next_line_tmp[k] = buff[k];
		k++;
	}
	next_line = ft_cat_free(next_line, next_line_tmp, k, flag);
	return (next_line);
}

static char	*ft_while_read(char *next_line, int i, char *buff)
{
	if (buff[i] == '\n')
		next_line = ft_creat_new(next_line, buff, 1, i);
	else
		next_line = ft_creat_new(next_line, buff, 0, i);
	return (next_line);
}

static char	*ft_read_buff(int fd, char *buff, char *next_line, int i)
{
	int	size;

	size = read(fd, buff, BUFFER_SIZE);
	if (size < 0)
	{
		free(next_line);
		return (NULL);
	}
	if (size != BUFFER_SIZE)
		buff[size] = 0;
	if (size == 0)
		return (next_line);
	if (buff[i] == '\n')
		next_line = ft_creat_new(next_line, buff, 0, 1);
	return (next_line);
}

static char	*ft_read_next(int fd, char *buff, int size)
{
	char	*next_line;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	next_line = buff;
	while ((buff[i] != '\n' || flag == 0) && buff[i] && next_line)
	{
		i = 0;
		while (buff[i] && buff[i] != '\n')
			i++;
		if (flag == 0)
			next_line = ft_while_read("\0", i, buff);
		else
			next_line = ft_while_read(next_line, i, buff);
		flag = 1;
		if (buff[i] == '\0' && size == BUFFER_SIZE)
		{
			i = 0;
			next_line = ft_read_buff(fd, buff, next_line, 0);
		}
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	buff[BUFFER_SIZE + 1];
	int			size;
	static int	fd_check;
	static int	flag;

	if (flag == 0)
		fd_check = fd;
	if (fd_check != fd)
		return (NULL);
	size = BUFFER_SIZE;
	if (fd < 0)
		return (NULL);
	if (buff[0] == 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size <= 0)
			return (NULL);
		if (size != BUFFER_SIZE)
			buff[size] = 0;
	}
	flag = 1;
	next_line = ft_read_next(fd, buff, size);
	ft_modif_buff(buff, BUFFER_SIZE);
	return (next_line);
}
