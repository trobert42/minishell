/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/28 10:14:56 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	hered_mode_error(t_data *data, t_block *b, t_list *lst)
{
	get_limiter_str(b, lst);
	data->hered_err_fd = open(".hd_tmp_err", O_WRONLY | O_CREAT, 0644);
	if (data->hered_err_fd < 0)
	{
		print_hered_fail(strerror(errno));
		return (g_var = EXIT_FAILURE, -1);
	}
	hered_mode_gnl(data, data->hered_err_fd, b->limiter);
	unlink(".hd_tmp_err");
	close(data->hered_err_fd);
	return (1);
}

int	here_doc_error3(t_list *lst, t_elem *redir)
{
	if ((!lst && redir->count < 4 && redir->type == '<') || \
	(!lst && redir->count < 3 && redir->type == '>'))
		return (-1);
	if ((lst && redir->count > 3) || (!lst && redir->count >= 3))
	{
		if ((redir->count == 3 && redir->type == '>') || \
		(redir->count == 4 && redir->type == '<'))
			return (-1);
		if ((redir->count >= 4 && redir->type == '>') || \
		(redir->count == 5 && redir->type == '<'))
			return (-1);
		if (redir->count >= 6 && redir->type == '<')
			return (-1);
	}
	if (lst && redir->count >= 1 && is_redir(lst) == 1 \
	&& redir->type != lst->str[0])
		return (-1);
	if (lst && is_pipe(lst) == 1)
		return (-1);
	return (1);
}

t_list	*here_doc_error2(t_list *lst, t_elem *redir)
{
	redir->type = (lst)->str[0];
	redir->count = 1;
	lst = lst->next;
	while (lst && is_redir(lst) == 1 && redir->type == lst->str[0])
	{
		redir->count++;
		lst = lst->next;
	}
	return (lst);
}

int	check_syntax_here_doc_error(t_data *data, t_block *b, t_list **tokenlst)
{
	t_list	*lst;
	t_elem	*redir;

	lst = *tokenlst;
	redir = godmalloc(NULL, 0, S_ELEM);
	while (lst)
	{
		if (is_redir(lst) == 1)
		{
			lst = here_doc_error2(lst, redir);
			if (redir->count == 2 && redir->type == '<' \
			&& lst && is_redir(lst) == -1)
				hered_mode_error(data, b, lst);
			if (here_doc_error3(lst, redir) == -1)
			{
				if (g_var != CTR_C_SIGNAL)
					g_var = MISUSE_SHELL;
				return (godmalloc(redir, 0, FREE_PTR), -1);
			}
		}
		if (lst)
			lst = lst->next;
	}
	return (godmalloc(redir, 0, FREE_PTR), 1);
}

void	hered_error(t_data *data, t_block **block)
{
	t_block	*b;

	b = *block;
	while (b && g_var != CTR_C_SIGNAL)
	{
		if (check_syntax_here_doc_error(data, b, b->tokenlst) == -1)
			return ;
		b = b->next;
	}
}
