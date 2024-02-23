/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 12:43:00 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_process(t_data *data, t_pipex *p, t_block *block, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	close_pipes(data->pipex, p->index);
	if (block->fd_in != -1 && dup2(block->fd_in, STDIN_FILENO) < 0)
		error_exit("dup2 fd_in as failed", strerror(errno));
	if (block->fd_out > 2)
	{
		if (dup2(block->fd_out, STDOUT_FILENO) < 0)
			error_exit("dup2 for fd_out has failed", strerror(errno));
	}
	else if (p->pipe_nbr > 0)
	{
		if (dup2(p->pipefd[0][1], STDOUT_FILENO) < 0)
			error_exit("dup2 for pipefd has failed", strerror(errno));
	}
	exec_cmd(data, p, block, envp);
}

void	nth_child(t_data *data, t_pipex *p, t_block *block, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	close_pipes(p, p->index);
	if (block->fd_in > 2)
	{
		if (dup2(block->fd_in, STDIN_FILENO) < 0)
			error_exit("dup2 for fd_in has failed", strerror(errno));
	}
	else
	{
		if (dup2(p->pipefd[p->index - 1][0], STDIN_FILENO) < 0)
			error_exit("dup2 for pipefd has failed", strerror(errno));
	}
	if (block->fd_out > 2)
	{
		if (dup2(block->fd_out, STDOUT_FILENO) < 0)
			error_exit("dup2 for fd_out has failed", strerror(errno));
	}
	else
	{
		if (dup2(p->pipefd[p->index][1], STDOUT_FILENO) < 0)
			error_exit("dup2 for pipefd has failed", \
			strerror(errno));
	}
	exec_cmd(data, p, block, envp);
}

void	last_process(t_data *data, t_pipex *p, t_block *block, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	close_pipes(p, p->index);
	if (block->fd_in > 2)
	{
		if (dup2(block->fd_in, STDIN_FILENO) < 0)
			error_exit("dup2 for fd_in has failed", strerror(errno));
	}
	else
	{
		if (dup2(p->pipefd[p->index - 1][0], STDIN_FILENO) < 0)
			error_exit("dup2 for pipefd has failed", strerror(errno));
	}
	if (block->fd_out != -1 && dup2(block->fd_out, STDOUT_FILENO) < 0)
		error_exit("dup2 for fd_out has failed", strerror(errno));
	exec_cmd(data, p, block, envp);
}

void	launch_forks(t_data *data, t_block **block, t_pipex *p)
{
	t_block	*b;

	b = *block;
	while (b)
	{
		p->pid[p->index] = fork();
		if (p->pid[p->index] < 0)
			error_exit("fork has failed", strerror(errno));
		if (b->id == 0 && p->pid[p->index] == 0)
			first_process(data, p, b, data->env_data->envp);
		else if (b->id == data->nbr_block - 1 && p->pid[p->index] == 0)
			last_process(data, p, b, data->env_data->envp);
		else if (b->id != 0 && p->pid[p->index] == 0)
			nth_child(data, p, b, data->env_data->envp);
		b = b->next;
		p->index++;
	}
	close_all_pipes(p);
	p->index = -1;
	while (++p->index != data->nbr_block)
		waitpid(p->pid[p->index], &p->status, 0);
}

int	ft_pipex(t_data *data)
{
	t_pipex	*p;
	int		i;

	i = 0;
	if (check_start_pipex(data) == -1)
		return (0);
	p = data->pipex;
	while (i < p->pipe_nbr)
	{
		if (pipe(p->pipefd[i++]) == -1)
		{
			write(STDERR_FILENO, "pipe for pipefd has failed :", 28);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			free_all_pipex(data, p);
			return (g_var = EXIT_FAILURE, -1);
		}
	}
	launch_forks(data, data->block, p);
	get_status_wait(p->status);
	free_all_pipex(data, p);
	return (1);
}
