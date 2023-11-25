/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:14:39 by faveline          #+#    #+#             */
/*   Updated: 2023/11/25 16:19:41 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_creat_env(int pid)
{
	char	*env[2];
	char	*itoa;

	itoa = ft_itoa(pid);
	env[0] = ft_strjoin("SYSTEMD_EXEC_PID=", itoa);
	free(itoa);
	env[1] = NULL;
	return (env);
}

static int	ft_child1(t_argv *var, int pid)
{
	char	**env;

	if (dup2(fd[0], var->infile) < 0)
		return (perror("error on dup2 child1 fd0\n"), -1);
	if (dup2(fd[1], 1) < 0)
		return (perror("error on dup2 child1 fd1\n"), -1);
	env = ft_creat_env(pid);
	if (execve(var->cmd1[0], var->cmd1, env) < 0)
		return (perror("error on cmd1\n"), free(env), -1);
	free(env);
	return (1);
}

static int	ft_child2(t_argv *var, int pid)
{
	char	**env;

	if (dup2(fd[0], 0) < 0)
		return (perror("error on dup2 child2 fd0\n"), -1);
	if (dup2(fd[1], var->outfile) < 0)
		return (perror("error on dup2 child2 fd1\n"), -1);
	env = ft_creat_env(pid);
	if (execve(var->cmd2[0], var->cmd2, env) < 0)
		return (perror("error on cmd2\n"), free(env), -1);
	free(env);
	return (1);
}

int	ft_pipe_fork(t_argv *var, t_pipe *pipex)
{
	if (pipe(pipex->fd) < 0)
		return (-1);

	pipex->child1 = fork();
	if (pipex->child1 < 0)
		return (perror("error creating child1\n"), -1);
	else if (pipex->child1 > 0) //parent
	{
		waitpid(pipe->child1, NULL, 0);
		pipex->child2 = fork();
		if (pipex->child2 < 0)
			return (perror("error creating child2\n"), -1);
		else if (pipex->child > 0) //parent
			waitpid(pipex->child2, NULL, 0);
		else //child2
		{
			if (ft_child2(var, pipex->child2) < 0)
				return (-1);
		}
	}
	else //child1
	{
		if (ft_child1(var, pipex->child1) < 0)
			return (-1);
	}
}
