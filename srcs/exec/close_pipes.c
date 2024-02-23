/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/20 12:10:38 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(t_pipex *p, int i)
{
	int	j;

	j = 0;
	while (j < p->pipe_nbr)
	{
		if (j != i)
			close(p->pipefd[j][1]);
		if (j != i - 1)
			close(p->pipefd[j][0]);
		j++;
	}
}

void	close_all_pipes(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < p->pipe_nbr)
	{
		close(p->pipefd[i][0]);
		close(p->pipefd[i][1]);
	}
}
