/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:14:39 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 12:20:39 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_child1(t_argv *var, t_pipe *pipex, char **envp)
{
	if (var->flag == 0)
	{
		if (access(var->cmd[0][0], F_OK | X_OK) < 0)
			return (ft_exterminate(var), perror("command not found"), -1);
		close(pipex->fd1[0]);
		if (dup2(var->infile, 0) < 0)
			return (perror("error on dup2 child1 fd0"), -1);
		if (dup2(pipex->fd1[1], 1) < 0)
			return (perror("error on dup2 child1 fd1"), -1);
		close(pipex->fd1[1]);
		if (execve(var->cmd[0][0], var->cmd[0], envp) < 0)
			return (perror("error on cmd1"), -1);
	}
	else
	{
		if (ft_here_doc(var, pipex, envp) < 0)
			return (-1);		
	}
	return (1);
}

int	ft_child2(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	if ((i - 1) % 2 != 0)
	{
		if (ft_child2_odd(var, pipex, envp) < 0)
			return (-1);
	}
	else
	{	
		if (ft_child2_even(var, pipex, envp) < 0)
			return (-1);
	}
	return (1);
}

int	ft_childx(t_argv *var, t_pipe *pipex, char **envp, int i)
{
	if ((i - 1) % 2 == 0)
	{
		if (ft_childx_even(var, pipex, envp, i) < 0)
			return (-1);
	}
	else
	{
		if (ft_childx_odd(var, pipex, envp, i) < 0)
			return (-1);
	}
	return (1);
}

int	ft_fork_x(t_argv *var, t_pipe *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex->childx = (pid_t *)malloc((var->nbr_cmd - 2) * sizeof(pid_t));
	if (pipex->childx == NULL)
		return (-1);
	while (i < var->nbr_cmd - 2)
	{
		if (i % 2 == 0 && pipe(pipex->fd2) < 0)
			return (perror("pipe creation failed"), free(pipex->childx), -1);
		else if (i % 2 != 0 && pipe(pipex->fd1) < 0)
			return (perror("pipe creation failed"), free(pipex->childx), -1);
		if (ft_fork_child_x(var, pipex, envp, i) < 0)
			return (free(pipex->childx), -1);
		i++;
	}
	free(pipex->childx);
	return (i + 1);
}

int	ft_pipe_fork(t_argv *var, t_pipe *pipex, char **env)
{
	int	i;

	if (pipe(pipex->fd1) < 0)
		return (perror("pipe cration failed"), -1);
	pipex->child1 = fork();
	if (pipex->child1 < 0)
		return (perror("error creating child1"), -1);
	else if (pipex->child1 > 0)
	{
		if (waitpid(pipex->child1, NULL, 0) < 0)
			return (perror("error waiting"), -1);
		i = ft_fork_x_i(var, pipex, env);
		if (i < 0)
			return (-1);
		if (ft_fork2(var, pipex, env, i) < 0)
			return (-1);
	}
	else
	{
		if (ft_child1(var, pipex, env) < 0)
			return (-1);
		ft_exterminate(var);
		exit(pipex->child1);
	}
	return (1);
}
