/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:28:24 by faveline          #+#    #+#             */
/*   Updated: 2023/11/25 16:30:40 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_pipex(int flag)
{
	if (flag == -1)
		ft_printf("Wrong number of arguments\n");
	if (flag == -2)
		ft_printf("Problem dealing with arguments\n");
	if (flag == -3)
		ft_printf("Pipe or fork error\n");
}

void	ft_delete(char *tab[])
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;	
	}
	free(tab);
}

void	ft_exterminate(t_argv *var)
{
	close(var->outfile);
	close(var->infile);
	if (var->cmd1)
		ft_delete(var->cmd1);
	if (var->cmd2)
		ft_delete(var->cmd2);
}
