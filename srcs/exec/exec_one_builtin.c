/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:32 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 12:27:12 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_one_builtin2(t_data *data, char **cmd)
{
	if (data->nbr_block == 1 && is_builtin(cmd[0]) == 1)
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
	}
}

int	exec_one_builtin(t_data *data, t_block *b, char **cmd)
{
	if (b->fd_in == -1 || b->fd_out == -1)
		return (0);
	if (is_builtin(b->cmd[0]) == 1)
	{
		data->saved_stdin = dup(STDIN_FILENO);
		data->saved_stdout = dup(STDOUT_FILENO);
		if (dup2(b->fd_in, STDIN_FILENO) < 0)
			return (g_var = 1, write(STDERR_FILENO, DUP2_ERR, 16), -1);
		if (dup2(b->fd_out, STDOUT_FILENO) < 0)
			return (g_var = 1, write(STDERR_FILENO, DUP2_ERR, 16), -1);
		exec_one_builtin2(data, cmd);
		if (dup2(data->saved_stdin, STDIN_FILENO) < 0)
			return (g_var = 1, write(STDERR_FILENO, DUP2_ERR, 16), -1);
		if (dup2(data->saved_stdout, STDOUT_FILENO) < 0)
			return (g_var = 1, write(STDERR_FILENO, DUP2_ERR, 16), -1);
		close(data->saved_stdin);
		close(data->saved_stdout);
	}
	return (1);
}
