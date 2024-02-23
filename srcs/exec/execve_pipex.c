/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:32 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 13:38:36 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_data *data, char **cmd)
{
	if (is_same(cmd[0], "echo") == 1)
		ft_echo(cmd);
	else if (is_same(cmd[0], "cd") == 1)
		ft_cd(&data->env_data, cmd);
	else if (is_same(cmd[0], "pwd") == 1)
		ft_pwd(&data->env_data);
	else if (is_same(cmd[0], "export") == 1)
		ft_export(&data->env_data, cmd);
	else if (is_same(cmd[0], "unset") == 1)
		ft_unset(&data->env_data, cmd);
	else if (is_same(cmd[0], "env") == 1)
		ft_env(&data->env_data, cmd);
	else if (is_same(cmd[0], "exit") == 1)
		ft_exit(data, cmd);
	godmalloc(NULL, 0, FREE_ALL);
}

void	exec_shell_function2(char **cmd, char **envp)
{
	if (cmd[0] && is_same_char('/', cmd[0]) == 1 && check_file(cmd[0]) == 1)
	{
		if (execve(cmd[0], cmd, envp) < 0)
			write(STDERR_FILENO, "Exec format error\n", 18);
	}
	else if ((cmd[0] && is_same_char('/', cmd[0]) == 0) || (cmd[0] && \
	check_file(cmd[0]) == 1))
	{
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		g_var = CMD_NOT_FOUND;
		godmalloc(NULL, 0, FREE_ALL);
	}
}

void	exec_shell_function(t_data *data, t_pipex *p, char **cmd, char **envp)
{
	int	i;

	i = 0;
	p->path_cmd = get_value_of(&data->env_data, "PATH");
	if (p->path_cmd && check_file(cmd[0]) != 0 && \
	is_same_char('/', cmd[0]) != 1)
	{
		p->potential_paths = ft_split(p->path_cmd, ':');
		godmalloc(p->path_cmd, 0, FREE_PTR);
		while (p->potential_paths[i])
		{
			p->path_cmd = ft_cmdjoin(p->potential_paths[i], cmd[0]);
			if (execve(p->path_cmd, cmd, envp) < 0)
				godmalloc(p->path_cmd, 0, FREE_PTR);
			i++;
		}
		free_split(p->potential_paths);
	}
	exec_shell_function2(cmd, envp);
	godmalloc(NULL, 0, FREE_ALL);
}

void	exec_cmd(t_data *data, t_pipex *p, t_block *b, char **envp)
{
	if ((b->cmd[0] == NULL && data->nbr_block > 1 && b->fd_in == -1) || \
	(b->cmd[0] == NULL && data->nbr_block > 1 && b->fd_in > 2))
	{
		g_var = EXIT_SUCCESS;
		godmalloc(NULL, 0, FREE_ALL);
	}
	if (b->fd_out == -1 || b->fd_in == -1)
	{
		g_var = EXIT_FAILURE;
		godmalloc(NULL, 0, FREE_ALL);
	}
	if (is_builtin(b->cmd[0]) == 1)
		exec_builtin(data, b->cmd);
	else
		exec_shell_function(data, p, b->cmd, envp);
}
