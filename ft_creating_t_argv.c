/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creating_t_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:22:16 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 15:34:28 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_check_cmd2(char **str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|')
				str[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (str);
}

static char	*ft_move_if_34(char *str, int i)
{
	if (str[i] == 92 && str[i + 1] == 34)
	{
		str[i] = 34;
		i++;
		while (str[i + 1] != '\0')
		{
			str[i] = str[i + 1];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

static char	*ft_check_cmd1(char *str)
{
	int		i;
	int		flag;
	int		i_c;

	i_c = 0;
	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (i_c == 0)
				str[i] = ' ';
			flag++;
			i_c = i;
		}
		str = ft_move_if_34(str, i);
		if (flag > 0 && i_c != i && str[i] == ' ')
			str[i] = '|';
		i++;
	}
	if (i_c > 0)
		str[i_c] = ' ';
	return (str);
}

static int	ft_creating_cmd(char *argv, char **cmd[])
{
	char	*str_trim;
	char	*str_join;

	str_trim = ft_strtrim(argv, " ");
	if (str_trim == NULL)
		return (-1);
	str_trim = ft_check_cmd1(str_trim);
	if (access(str_trim, F_OK) < 0)
		*cmd = ft_split(str_trim, ' ');
	else
		*cmd = ft_split(str_trim, '\0');
	free(str_trim);
	if (*cmd == NULL)
		return (-1);
	*cmd = ft_check_cmd2(*cmd);
	if (access(*cmd[0], F_OK) == 0)
		return (1);
	else
	{
		str_join = ft_strjoin("/bin/", *cmd[0]);
		free(*cmd[0]);
		*cmd[0] = ft_strjoin(str_join, "");
		free(str_join);
	}
	return (1);
}

int	ft_creating_t_argv(char *argv[], t_argv *var)
{
	var->infile = open(argv[1], O_RDONLY);
	if (var->infile < 0)
		return (-1);
	var->outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 00777);
	if (var->outfile < 0)
		return (close(var->infile), -1);
	if (ft_creating_cmd(argv[2], &var->cmd1) < 0)
		return (ft_exterminate(var), -1);
	if (ft_creating_cmd(argv[3], &var->cmd2) < 0)
		return (ft_exterminate(var), -1);
	return (1);
}
