/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:14:39 by faveline          #+#    #+#             */
/*   Updated: 2023/11/25 18:44:30 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_creat_env(int pid)
{
	char	**env;
	char	*itoa;

	itoa = ft_itoa(pid);
	env = (char **)malloc(2 * sizeof(char *));
	env[0] = ft_strjoin("SYSTEMD_EXEC_PID=", itoa);
	free(itoa);
	env[1] = NULL;
	return (env);
}

static int	ft_child1(t_argv *var, t_pipe *pipex, char **envp)
{
	char	**env;

	ft_printf("child1\n");
	close(pipex->fd[0]);
	if (dup2(var->infile, 0) < 0)
		return (perror("error on dup2 child1 fd0\n"), -1);
	if (dup2(pipex->fd[1], 1) < 0)
		return (perror("error on dup2 child1 fd1\n"), -1);
	env = ft_creat_env((int)pipex->child1);
	if (execve(var->cmd1[0], var->cmd1, envp) < 0)
		return (perror("error on cmd1\n"), ft_delete(env), close(pipex->fd[1]), -1);
	close(pipex->fd[1]);
	ft_delete(env);
	return (1);
}

static int	ft_child2(t_argv *var, t_pipe *pipex, char **envp)
{
	char	**env;

	ft_printf("child2\n");
	close(pipex->fd[1]);
	if (dup2(var->outfile, 1) < 0)
		return (perror("error on dup2 child2 fd1\n"), -1);
	if (dup2(pipex->fd[0], 0) < 0)
		return (perror("error on dup2 child2 fd0\n"), -1);
	env = ft_creat_env((int)pipex->child2);
	close(pipex->fd[0]);
	if (execve(var->cmd2[0], var->cmd2, envp) < 0)
		return (perror("error on cmd2\n"), ft_delete(env), close(pipex->fd[0]), 1);

	ft_delete(env);
	return (1);
}

int	ft_pipe_fork(t_argv *var, t_pipe *pipex, char **env)
{
	if (pipe(pipex->fd) < 0)
		return (-1);

	pipex->child1 = fork();
	if (pipex->child1 < 0)
		return (perror("error creating child1\n"), -1);
	else if (pipex->child1 > 0) //parent
	{
		waitpid(pipex->child1, NULL, 0);
		pipex->child2 = fork();
		if (pipex->child2 < 0)
			return (perror("error creating child2\n"), -1);
		else if (pipex->child2 > 0) //parent
			waitpid(pipex->child2, NULL, 0);
		else //child2
		{
			if (ft_child2(var, pipex, env) < 0)
				return (-1);
		}
	}
	else //child1
	{
		if (ft_child1(var, pipex, env) < 0)
			return (-1);
		ft_printf("child1 over");
	}
	return (1);
}
