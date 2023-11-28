/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:14:39 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 15:45:25 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_child1(t_argv *var, t_pipe *pipex, char **envp)
{
	if (access(var->cmd1[0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	close(pipex->fd[0]);
	if (dup2(var->infile, 0) < 0)
		return (perror("error on dup2 child1 fd0"), -1);
	if (dup2(pipex->fd[1], 1) < 0)
		return (perror("error on dup2 child1 fd1"), -1);
	close(pipex->fd[1]);
	if (execve(var->cmd1[0], var->cmd1, envp) < 0)
		return (perror("error on cmd1"), close(pipex->fd[1]), -1);
	return (1);
}

static int	ft_child2(t_argv *var, t_pipe *pipex, char **envp)
{
	if (access(var->cmd2[0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	if (dup2(pipex->fd[0], 0) < 0)
		return (perror("error on dup2 child2 fd0"), -1);
	if (dup2(var->outfile, 1) < 0)
		return (perror("error on dup2 child2 fd1"), -1);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	if (execve(var->cmd2[0], var->cmd2, envp) < 0)
		return (perror("error on cmd2"), close(pipex->fd[0]), -1);
	return (1);
}

static int	ft_fork2(t_argv *var, t_pipe *pipex, char **env)
{
	pipex->child2 = fork();
	if (pipex->child2 < 0)
		return (perror("error creating child2"), -1);
	else if (pipex->child2 == 0)
	{
		if (ft_child2(var, pipex, env) < 0)
			return (-1);
	}
	else if (pipex->child2 > 0)
	{
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		if (waitpid(pipex->child2, NULL, 0) < 0)
			return (perror("error while waiting"), -1);
	}
	return (1);
}

int	ft_pipe_fork(t_argv *var, t_pipe *pipex, char **env, char *argv[])
{
	if (pipe(pipex->fd) < 0)
		return (perror("pipe ceration failed"), -1);
	pipex->child1 = fork();
	if (pipex->child1 < 0)
		return (perror("error creating child1"), -1);
	else if (pipex->child1 > 0)
	{
		if (ft_strncmp(argv[1], "/dev/urandom", 12) != 0
			&& waitpid(pipex->child1, NULL, 0) < 0)
			return (perror("error while waiting"), -1);
		if (ft_fork2(var, pipex, env) < 0)
			return (-1);
	}
	else
	{
		if (ft_child1(var, pipex, env) < 0)
			return (-1);
	}
	return (1);
}
