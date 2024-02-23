/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:32 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pid(t_pipex *p, int nbr_block)
{
	int	i;

	p->pid = godmalloc(NULL, nbr_block, TAB_INT);
	i = 0;
	while (i < nbr_block)
		p->pid[i++] = -1;
}

void	init_pipefd(t_pipex *p, int nbr_pipe)
{
	int	i;

	i = 0;
	p->pipefd = godmalloc(NULL, nbr_pipe, TAB_INT);
	while (i < nbr_pipe)
	{
		p->pipefd[i] = godmalloc(NULL, 2, TAB_INT);
		p->pipefd[i][0] = 0;
		p->pipefd[i][1] = 0;
		i++;
	}
}

int	count_pipes(t_block **block)
{
	t_block	*b;
	int		i;

	i = 0;
	b = *block;
	while (b)
	{
		i++;
		b = b->next;
	}
	return (i);
}

int	count_cmds(t_block **block)
{
	t_block	*b;
	int		i;

	i = 0;
	b = *block;
	while (b)
	{
		if (b->cmd && b->cmd[0] != NULL)
			i++;
		b = b->next;
	}
	return (i);
}

void	init_var_pipex(t_data *data)
{
	t_pipex	*p;

	p = godmalloc(NULL, 0, S_PIPEX);
	data->pipex = p;
	p->index = 0;
	p->cmd_nbr = count_cmds(data->block);
	p->pipe_nbr = count_pipes(data->block) - 1;
	p->potential_paths = NULL;
	p->path_cmd = NULL;
	p->pipefd = NULL;
	init_pid(p, data->nbr_block);
	if (p->pipe_nbr > 0)
		init_pipefd(p, p->pipe_nbr);
}
