/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:47:47 by faveline          #+#    #+#             */
/*   Updated: 2023/11/27 16:27:25 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_argv
{
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
}			t_argv;

typedef struct s_pipe
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
}			t_pipe;

int		ft_creating_t_argv(char *argv[], t_argv *var);
void	ft_error_pipex(int flag);
void	ft_delete(char *tab[]);
void	ft_exterminate(t_argv *var);
int		ft_pipe_fork(t_argv *var, t_pipe *pipe, char **env, char *argv[]);

#endif
