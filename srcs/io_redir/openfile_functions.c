/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/29 14:02:06 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	openfile_redir_in(t_list *lst, t_block *block)
{
	if (lst->prev && lst->prev->type == REDIR_IN)
	{
		if (block->fd_in > 2)
			close(block->fd_in);
		block->fd_in = open(lst->str, O_RDONLY);
		if (block->fd_in < 0)
		{
			write(STDERR_FILENO, lst->str, ft_strlen(lst->str));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, " \n", 2);
			return (-1);
		}
	}
	return (1);
}

int	openfile_heredoc2(t_list *lst, t_block *block)
{
	if (lst->prev && lst->prev->type == HERE_DOC)
	{
		if (block->fd_in > 2)
			close(block->fd_in);
		if (block->fd_hd < 0)
			block->fd_in = -1;
		else
		{
			block->fd_in = open(block->hd_name, O_RDONLY, 0644);
			block->fd_hd = block->fd_in;
			if (block->fd_in < 0)
			{
				block->fd_in = -1;
				return (-1);
			}
		}
	}
	return (1);
}

int	openfile_heredoc(t_data *data, t_list *lst, t_block *block)
{
	if (lst->prev && lst->prev->type == HERE_DOC)
	{
		block->hd_name = ft_strjoin(".hd_tmp", ft_itoa(block->id));
		if (block->fd_in > 2)
			close(block->fd_in);
		block->fd_in = open(block->hd_name, O_CREAT | O_WRONLY, 0644);
		if (block->fd_in < 0)
		{
			write(STDERR_FILENO,
				"can't create tmp file for here document: ", 41);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, " \n", 2);
			return (-1);
		}
		block->fd_hd = block->fd_in;
		get_limiter_str(block, lst);
		hered_mode(data, block);
	}
	return (1);
}

int	openfile_redir_out(t_list *lst, t_block *block)
{
	if (lst->prev && lst->prev->type == REDIR_OUT)
	{
		if (block->fd_out > 2)
			close(block->fd_out);
		block->fd_out = open(lst->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (block->fd_out < 0)
		{
			write(STDERR_FILENO, lst->str, ft_strlen(lst->str));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, " \n", 2);
			return (-1);
		}
	}
	return (1);
}

int	openfile_append(t_list *lst, t_block *block)
{
	if (lst->prev && lst->prev->type == APPEND)
	{
		if (block->fd_out > 2)
			close(block->fd_out);
		block->fd_out = open(lst->str, O_CREAT | O_APPEND | O_WRONLY, 0666);
		if (block->fd_out < 0)
		{
			write(STDERR_FILENO, lst->str, ft_strlen(lst->str));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, " \n", 2);
			return (-1);
		}
	}
	return (1);
}
