/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_all_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/29 14:02:06 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_files_per_block(t_block *b, t_list **tokenlst)
{
	t_list	*lst;

	lst = *tokenlst;
	while (lst)
	{
		if (lst->type == DIRFILE || lst->type == LIMITER)
		{
			if (openfile_redir_in(lst, b) == -1)
				return (-1);
			else if (openfile_heredoc2(lst, b) == -1)
				return (-1);
			else if (openfile_redir_out(lst, b) == -1)
				return (-1);
			else if (openfile_append(lst, b) == -1)
				return (-1);
		}
		if (lst->type == COMMAND && !is_builtin(b->cmd[0]) \
		&& is_same_char('/', lst->str) == 1)
			is_file(lst->str, b->cmd[0]);
		lst = lst->next;
	}
	return (1);
}

int	open_heredoc_per_block(t_data *data, t_block *b, t_list **tokenlst)
{
	t_list	*lst;

	lst = *tokenlst;
	while (lst)
	{
		if (lst->type == DIRFILE || lst->type == LIMITER)
		{
			if (openfile_heredoc(data, lst, b) == -1 || g_var == 130)
				return (-1);
		}
		lst = lst->next;
	}
	return (1);
}

int	open_all_heredoc(t_data *data, t_block **block)
{
	t_block	*b;
	int		error;

	error = 1;
	b = *block;
	while (b && g_var != CTR_C_SIGNAL)
	{
		if (open_heredoc_per_block(data, b, b->tokenlst) == -1)
		{
			error = -1;
			if (g_var != CTR_C_SIGNAL)
				g_var = EXIT_FAILURE;
		}
		b = b->next;
	}
	return (error);
}

int	open_all_files(t_data *data, t_block **block)
{
	t_block	*b;
	int		error;

	b = *block;
	open_all_heredoc(data, block);
	while (b && g_var != CTR_C_SIGNAL)
	{
		error = 1;
		if (open_files_per_block(b, b->tokenlst) == -1)
		{
			error = -1;
			if (g_var != CTR_C_SIGNAL)
				g_var = EXIT_FAILURE;
		}
		b = b->next;
	}
	return (error);
}
