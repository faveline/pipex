/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:47:47 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 12:21:52 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_argv
{
	int		infile;
	int		outfile;
	char	***cmd;
	int		flag;
	char	*lim;
	int		nbr_cmd;
}			t_argv;

typedef struct s_pipe
{
	int		fd1[2];
	int		fd2[2];
	pid_t	child1;
	pid_t	child2;
	pid_t	*childx;
}			t_pipe;

int		ft_creating_t_argv(int argc, char *argv[], t_argv *var);
void	ft_error_pipex(int flag);
void	ft_delete(char *tab[]);
void	ft_exterminate(t_argv *var);
int		ft_pipe_fork(t_argv *var, t_pipe *pipe, char **env);
int		ft_child2_even(t_argv *var, t_pipe *pipex, char **envp);
int		ft_child2_odd(t_argv *var, t_pipe *pipex, char **envp);
int		ft_childx_even(t_argv *var, t_pipe *pipex, char **envp, int i);
int		ft_childx_odd(t_argv *var, t_pipe *pipex, char **envp, int i);
void	ft_close_parent(t_pipe *pipex, int i, int flag);
int		ft_fork_child_x(t_argv *var, t_pipe *pipex, char **envp, int i);
int		ft_childx(t_argv *var, t_pipe *pipex, char **envp, int i);
int		ft_fork_x(t_argv *var, t_pipe *pipex, char **envp);
int		ft_fork_x_i(t_argv *var, t_pipe *pipex, char **envp);
int		ft_child2(t_argv *var, t_pipe *pipex, char **envp, int i);
int		ft_fork2(t_argv *var, t_pipe *pipex, char **envp, int i);
int		ft_here_doc(t_argv *var, t_pipe *pipex, char **envp);

#endif
