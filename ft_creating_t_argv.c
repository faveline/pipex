/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creating_t_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:22:16 by faveline          #+#    #+#             */
/*   Updated: 2023/11/25 16:22:44 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_creating_cmd(char *argv, char *cmd[])
{
	char	*str_trim;
	char	*str_join;

	str_trim = ft_strtrim(argv, " ");
	if (str_trim == NULL)
		return (-1);
	str_join = ft_strjoin("/bin/", str_trim);
	free(str_trim);
	if (str_join == NULL)
		return (-1);
	cmd = ft_split(str_join, ' ');
	free(str_join);
	if (cmd == NULL)
		return (-1);
	return (1);
}

int	ft_creating_t_Argv(char *argv[], t_argv *var)
{
	var->infile = open(argv[1], O_RDONLY);
	if (var->infile < 0)
		return (-1);
	var->outfile = open(argv[4], O_WRONLY);
	if (var->outfile < 0)
		return (close(var->infile), -1);
	if (ft_creating_cmd(argv[2], var->cmd1) < 0)
		return (ft_exterminate(var), -1);
	if (ft_creating_cmd(argv[3], var->cmd2) < 0)
		return (ft_exterminate(var), -1);
	return (1);
}
