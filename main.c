/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:09:42 by faveline          #+#    #+#             */
/*   Updated: 2023/11/24 14:53:57 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	if (argc != 5)
		return (1);
	
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	int		fd_file;

	fd_file = open(argv[1], O_RDONLY);
	if (fd_file < 0)
	{
		ft_printf("Opening file error");
		return (1)
	}

	if (pipe(fd) == -1)
	{
		ft_printf("Pipe error");
		return (1);	
	}

	child1 = fork();
	if (child1 < 0)
	{
		ft_printf("Fork error");
		return (1);	
	}
	else if (child1 > 0)
	{
		dup2(fd_file, fd[0]);
		close(fd[1]);
		wait_pid(child1, NULL, 0);
	
	
	
	}
	else
	{
		execve();	
	}
	close(fd_file);
}
