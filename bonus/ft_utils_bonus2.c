/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:40:56 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 12:41:17 by faveline         ###   ########.fr       */
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

static int	ft_creat_here_doc(t_argv *var)
{
	int		fd;
	char	*next_line;

	fd = open(here_doc, O_RDWR | O_CREAT | O_TRUNC, 00777);
	ft_printf("pipe heredoc> ");
	next_line = get_next_line(0);
	if (next_line == NULL)
		return (-1);
	while (ft_strncmp(next_line, var->lim, ft_strlen(var->lim)) != 0)
	{
		ft_putstr_fd(next_line, fd);
		free(next_line);
		ft_printf("pipe heredoc> ");	
		next_line = get_next_line(0);
		if (next_line == NULL)
			return (-1);
	}
	return (fd);
}

int	ft_here_doc(t_argv *var, t_pipe *pipex, char **envp)
{
	int	fd_here_doc;
	
	fd_here_doc = ft_creat_here_doc(t_argv *var);
	if (here_doc < 0)
		return (-1);
	if (access(var->cmd[0][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	close(pipex->fd1[0]);
	if (dup2(fd_here_doc, 0) < 0)
		return (perror("error on dup2 child1 fd0"), -1);
	if (dup2(pipex->fd1[1], 1) < 0)
		return (perror("error on dup2 child1 fd1"), -1);
	close(pipex->fd1[1]);
	if (execve(var->cmd[0][0], var->cmd[0], envp) < 0)
		return (perror("error on cmd1"), -1);
	return (1);
}
