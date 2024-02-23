/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 13:21:58 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_cmdjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	str = godmalloc(NULL, s1_len + s2_len + 2, STR);
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (i < (s1_len + 1 + s2_len))
		str[i++] = s2[j++];
	str[s1_len + s2_len + 1] = '\0';
	return (str);
}

void	free_all_pipex(t_data *data, t_pipex *p)
{
	if (p->path_cmd)
		godmalloc(p->path_cmd, 0, FREE_PTR);
	if (p->potential_paths)
		free_split(p->potential_paths);
	if (p->pid)
		godmalloc(p->pid, 0, FREE_PTR);
	if (p->pipefd)
		free_int_split(p->pipefd, p->pipe_nbr);
	if (p)
		godmalloc(p, 0, FREE_PTR);
	data->nbr_pipe = 0;
}

void	error_exit(char *err, char *strerr)
{
	if (!err && !strerr)
	{
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerr, ft_strlen(strerr));
		write(STDERR_FILENO, " \n", 2);
	}
	else if (!strerr)
	{
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, " \n", 2);
	}
	g_var = EXIT_FAILURE;
	godmalloc(NULL, 0, FREE_ALL);
}

int	check_start_pipex(t_data *data)
{
	if (g_var == CTR_C_SIGNAL)
		return (-1);
	if (data->nbr_block == 1 && is_builtin((*data->block)->cmd[0]) == 1)
		return (-1);
	init_var_pipex(data);
	if (data->nbr_pipe > 120)
	{
		write(STDERR_FILENO, "too much pipe, stack overflow possible \n", 40);
		free_all_pipex(data, data->pipex);
		return (g_var = EXIT_FAILURE, -1);
	}
	return (0);
}

void	get_status_wait(int status)
{
	if (WIFSIGNALED(status))
	{
		if (status == 131)
		{
			g_var = COREDUMP;
			write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		}
	}
	else if (WIFEXITED(status))
		g_var = WEXITSTATUS(status);
}
