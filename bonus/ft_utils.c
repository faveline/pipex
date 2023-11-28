/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:28:24 by faveline          #+#    #+#             */
/*   Updated: 2023/11/28 14:47:40 by faveline         ###   ########.fr       */
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
	int	i;

	if (var->flag == 0 && var->infile > 0)
		close(var->infile);
	else if (var->flag == 1)
		free(var->lim);
	if (var->outfile > 0)
		close(var->outfile);
	i = 0;
	while (i < var->nbr_cmd && var->cmd[i])
	{
		ft_delete(var->cmd[i]);
		i++;
	}
	if (var->cmd)
		free(var->cmd);
	if (var->flag == 1)
		unlink("/tmp/here_doc");
}
