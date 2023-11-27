/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:09:42 by faveline          #+#    #+#             */
/*   Updated: 2023/11/27 17:01:04 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_argv	var;
	t_pipe	pipex;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		var.lim = ft_strjoin(argv[2], "");
		if (var.lim == NULL)
			return (ft_error_pipex(-1), 1);
		var.flag = 1;
	}
	else
		var.flag = 0;
	if (argc < 5 || (argc < 6 && var.flag == 1))
		return (ft_error_pipex(-1), 1);
	if (ft_creating_t_argv(argc, argv, &var) < 0)
		return (ft_error_pipex(-2), 1);
	if (ft_pipe_fork(&var, &pipex, env) < 0)
		return (ft_error_pipex(-3), 1);
	ft_exterminate(&var);
//	free(pipex.fd[0]);
//	free(pipex.fd[1]);
	return (0);
}
