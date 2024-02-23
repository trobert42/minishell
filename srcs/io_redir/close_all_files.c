/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 12:33:26 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_saved_dup(t_data *data)
{
	if (data->saved_stdin != -1)
		close(data->saved_stdin);
	if (data->saved_stdout != -1)
		close(data->saved_stdout);
	if (data->saved_stdin_loop != -1)
		close(data->saved_stdin_loop);
}

void	close_all_files(t_block **block)
{
	t_block	*b;

	b = *block;
	while (b)
	{
		if (b->fd_in != -1 && b->fd_in > 2)
			close(b->fd_in);
		if (b->fd_out != -1 && b->fd_out > 2)
			close(b->fd_out);
		if (b->fd_hd != -1)
		{
			close(b->fd_hd);
			if (b->hd_name)
				unlink(b->hd_name);
		}
		b = b->next;
	}
}

int	check_file(char *pathname)
{
	DIR	*dir;

	if (!pathname)
		return (3);
	dir = opendir(pathname);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			if (access(pathname, X_OK | R_OK) == -1)
				return (2);
			return (1);
		}
		return (3);
	}
	closedir(dir);
	return (0);
}
