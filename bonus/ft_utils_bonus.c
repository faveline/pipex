/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:08:24 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 11:37:29 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child2_even(t_argv *var, t_pipe *pipex, char **envp)
{
	if (access(var->cmd[var->nbr_cmd - 1][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	if (dup2(pipex->fd1[0], 0) < 0)
		return (perror("error on dup2 child2 fd0"), -1);
	if (dup2(var->outfile, 1) < 0)
		return (perror("error on dup2 child2 fd1"), -1);
	close(pipex->fd1[1]);
	close(pipex->fd1[0]);
	if (execve(var->cmd[var->nbr_cmd - 1][0],
		var->cmd[var->nbr_cmd - 1], envp) < 0)
		return (perror("error on cmd2"), -1);
	return (1);
}

int	ft_child2_odd(t_argv *var, t_pipe *pipex, char **envp)
{
	if (access(var->cmd[var->nbr_cmd - 1][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	if (dup2(pipex->fd2[0], 0) < 0)
		return (perror("error on dup2 child2 fd0"), -1);
	if (dup2(var->outfile, 1) < 0)
		return (perror("error on dup2 child2 fd1"), -1);
	close(pipex->fd2[1]);
	close(pipex->fd2[0]);
	if (execve(var->cmd[var->nbr_cmd - 1][0],
		var->cmd[var->nbr_cmd - 1], envp) < 0)
		return (perror("error on cmd2"), -1);
	return (1);
}

int	ft_childx_even(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	if (access(var->cmd[i][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	close(pipex->fd1[1]);
	close(pipex->fd2[0]);
	if (dup2(pipex->fd2[1], 1) < 0)
		return (perror("error on dup2 childx fd1"), -1);
	if (dup2(pipex->fd1[0], 0) < 0)
		return (perror("error on dup2 childx fd0"), -1);
	close(pipex->fd1[0]);
	close(pipex->fd2[1]);
	if (execve(var->cmd[i][0], var->cmd[i], envp) < 0)
		return (perror("error on cmd2"), -1);
	return (1);
}

int	ft_childx_odd(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	if (access(var->cmd[i][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	close(pipex->fd2[1]);
	close(pipex->fd1[0]);
	if (dup2(pipex->fd2[0], 0) < 0)
		return (perror("error on dup2 childx fd0"), -1);
	if (dup2(pipex->fd1[1], 1) < 0)
		return (perror("error on dup2 childx fd1"), -1);
	close(pipex->fd2[0]);
	close(pipex->fd1[1]);
	if (execve(var->cmd[i][0], var->cmd[i], envp) < 0)
		return (perror("error on cmd2"), -1);
	return (1);
}

void	ft_close_parent(t_pipe *pipex, int i, int flag)
{
	if ((i % 2 == 0 && flag == 0) || (i % 2 != 0 && flag == 1))
	{
		close(pipex->fd1[0]);
		close(pipex->fd1[1]);
	}
	else if ((i % 2 != 0 && flag == 0) || (i % 2 == 0 && flag == 1))
	{	
		close(pipex->fd2[0]);
		close(pipex->fd2[1]);
	}
}
