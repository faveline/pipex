/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:40:56 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 14:11:05 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fork_child_x(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	pipex->childx[i] = fork();
	if (pipex->childx[i] < 0)
		return (perror("error forking childx"), -1);
	else if (pipex->childx[i] == 0)
	{
		if (ft_childx(var, pipex, envp, i + 1) < 0)
			return (free(pipex->childx), -1);
		ft_exterminate(var);
		free(pipex->childx);
		exit(pipex->childx[i]);
	}
	else if (pipex->childx[i] > 0)
	{
		ft_close_parent(pipex, i, 0);
		if (waitpid(pipex->childx[i], NULL, 0) < 0)
			return (perror("error waiting"), -1);
	}
	return (1);
}

int	ft_fork_x_i(t_argv *var, t_pipe *pipex, char **envp)
{
	int	i;

	i = 1;
	if (var->nbr_cmd >= 3)
		i = ft_fork_x(var, pipex, envp);
	return (i);
}

int	ft_fork2(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	pipex->child2 = fork();
	if (pipex->child2 < 0)
		return (perror("error creating child2"), -1);
	else if (pipex->child2 == 0)
	{
		if (ft_child2(var, pipex, envp, i) < 0)
			return (-1);
	}
	else if (pipex->child2 > 0)
		ft_close_parent(pipex, i, 1);
	return (1);
}
