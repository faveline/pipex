/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:09:42 by faveline          #+#    #+#             */
/*   Updated: 2023/11/26 13:47:36 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_argv	var;
	t_pipe	pipex;

	if (argc != 5)
		return (ft_error_pipex(-1), 1);
	if (ft_creating_t_argv(argv, &var) < 0)
		return (ft_error_pipex(-2), 1);
	if (ft_pipe_fork(&var, &pipex, env) < 0)
		return (ft_error_pipex(-3), 1);
	ft_exterminate(&var);
	return (0);
}
