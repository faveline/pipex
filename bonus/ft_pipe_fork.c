/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:14:39 by faveline          #+#    #+#             */
/*   Updated: 2023/11/27 15:25:57 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_child1(t_argv *var, t_pipe *pipex, char **envp)
{
	if (access(var->cmd[0][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	close(pipex->fd[0]);
	if (dup2(var->infile, 0) < 0)
		return (perror("error on dup2 child1 fd0"), -1);
	if (dup2(pipex->fd[1], 1) < 0)
		return (perror("error on dup2 child1 fd1"), -1);
	if (execve(var->cmd[0][0], var->cmd[0], envp) < 0)
		return (perror("error on cmd1"), close(pipex->fd[1]), -1);
	close(pipex->fd[1]);
	return (1);
}

static int	ft_child2(t_argv *var, t_pipe *pipex, char **envp)
{
	if (access(var->cmd[var->nbr_cmd - 1][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	if (dup2(pipex->fd[0], 0) < 0)
		return (perror("error on dup2 child2 fd0"), -1);
	if (dup2(var->outfile, 1) < 0)
		return (perror("error on dup2 child2 fd1"), -1);
	close(pipex->fd[1]);
	if (execve(var->cmd[var->nbr_cmd - 1][0], var->cmd[var->nbr_cmd - 1], envp) < 0)
		return (perror("error on cmd2"), close(pipex->fd[0]), -1);
	close(pipex->fd[0]);
	return (1);
}

static int	ft_childx(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	ft_printf("%s\n", var->cmd[i][2]);
	if (access(var->cmd[i][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	if (dup2(pipex->fd[0], 0) < 0)
		return (perror("error on dup2 childx fd0"), -1);
	if (dup2(pipex->fd[1], 1) < 0)
		return (perror("error on dup2 childx fd1"), -1);
	if (execve(var->cmd[i][0], var->cmd[i], envp) < 0)
		return (perror("error on cmd2"), close(pipex->fd[0]), close(pipex->fd[1]), -1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	return (1);
}

static int	ft_fork_x(t_argv *var, t_pipe *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex->childx = (pid_t *)malloc((var->nbr_cmd - 2) * sizeof(pid_t));
	if (pipex->childx == NULL)
		return (-1);
	while (i < var->nbr_cmd - 2)
	{
		pipex->childx[i] = fork();
		if (pipex->childx[i] < 0)
			return (perror("error forking childx"), free(pipex->childx), -1);
/*		else if (pipex->childx[i] > 0)
		{
			if (waitpid(pipex->childx[i], NULL, 0) < 0)
				return (perror("error waiting"), -1);
		}
*/		else if (pipex->childx[i] == 0)
		{
			if (ft_childx(var, pipex, envp, i + 1) < 0)
				return (free(pipex->childx), -1);		
		}
		i++;
	}
	free(pipex->childx);
	return (1);
}

int	ft_pipe_fork(t_argv *var, t_pipe *pipex, char **env)
{
	if (pipe(pipex->fd) < 0)
		return (perror("pipe ceration failed"), -1);
	pipex->child1 = fork();
	if (pipex->child1 < 0)
		return (perror("error creating child1"), -1);
	else if (pipex->child1 > 0)
	{
		if (waitpid(pipex->child1, NULL, 0) < 0)
			return (perror("error waiting"), -1);
		if (var->nbr_cmd >= 3 && ft_fork_x(var, pipex, env) < 0)
			return (-1);
		pipex->child2 = fork();
		if (pipex->child2 < 0)
			return (perror("error creating child2"), -1);
		else if (pipex->child2 == 0)
		{
			if (ft_child2(var, pipex, env) < 0)
				return (-1);
		}
	}
	else
	{
		if (ft_child1(var, pipex, env) < 0)
			return (-1);
	}
	return (1);
}
