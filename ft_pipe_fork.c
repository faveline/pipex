/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:14:39 by faveline          #+#    #+#             */
/*   Updated: 2023/11/25 15:38:16 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipe_fork(t_argv *var, t_pipe *pipex)
{
	if (pipe(pipex->fd) < 0)
		return (-1);

	pipe->child1 = fork();
	if (pipe->child1 < 0)
		return (perror("error creating child1\n"), -1);
	else if (pipe->child1 > 0) //parents
	{
		waitpid(pipe->child1, NULL, 0);
	
	
	
	}
	else //child1
	{
		close(fd[0]);
		if (dup2(fd[1], 1) < 0)
			return (perror("error on dup2 child1\n"), -1);
		if (execve(var->cmd1[0], var->cmd1, NULL) < 0)
			return (perror("error on cmd1\n"), -1);
	}

}
