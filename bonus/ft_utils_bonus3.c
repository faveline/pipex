/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:10:16 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 14:50:50 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_creat_here_doc(t_argv *var)
{
	char	*next_line;
	int		fd;

	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 00777);
	if (fd < 0)
		return (-1);
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
	free(next_line);
	close(fd);
	fd = open("/tmp/here_doc", O_RDWR);
	return (fd);
}

int	ft_here_doc(t_argv *var, t_pipe *pipex, char **envp)
{
	int	fd;

	fd = ft_creat_here_doc(var);
	if (fd < 0)
		return (-1);
	if (access(var->cmd[0][0], F_OK | X_OK) < 0)
		return (ft_exterminate(var), perror("command not found"), -1);
	close(pipex->fd1[0]);
	if (dup2(fd, 0) < 0)
		return (perror("error on dup2 child1 fd0"), -1);
	if (dup2(pipex->fd1[1], 1) < 0)
		return (perror("error on dup2 child1 fd1"), -1);
	close(pipex->fd1[1]);
	if (execve(var->cmd[0][0], var->cmd[0], envp) < 0)
		return (perror("error on cmd1"), -1);
	close(fd);
	return (1);
}
