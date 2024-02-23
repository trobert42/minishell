/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 12:28:04 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_bonus_error(t_list **list)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = *list;
	while (lst)
	{
		if (i == 0 && lst && is_pipe(lst) == 1 && \
		lst->next && is_pipe(lst->next) == 1)
			return (g_var = MISUSE_SHELL,
				write(STDERR_FILENO, TOKEN_ERR"`||' \n", 6), -1);
		if (lst && is_pipe(lst) == 1 && lst->next && is_pipe(lst->next) == 1)
		{
			if (lst->next->next && is_pipe(lst->next->next) == 1)
				return (g_var = MISUSE_SHELL, print_single_pipe_error(), -1);
			return (g_var = MISUSE_SHELL,
				write(STDERR_FILENO, "not doing bonuses\n", 18), -1);
		}
		lst = lst->next;
		i++;
	}
	return (1);
}

int	check_syntax3(t_list *lst, t_elem *redir)
{
	if ((!lst && redir->count < 4 && redir->type == '<') || \
	(!lst && redir->count < 3 && redir->type == '>'))
		return (print_newline_error(), -1);
	if ((lst && redir->count >= 3) || (!lst && redir->count >= 3))
	{
		if ((redir->count == 3 && redir->type == '>') || \
		(redir->count == 4 && redir->type == '<'))
			return (print_sep_error_simple(redir->type), -1);
		if (redir->count == 3 && redir->type == '<')
			return (write(STDERR_FILENO,
					"here_string not managed\n", 24), -1);
		if ((redir->count >= 4 && redir->type == '>') || \
		(redir->count == 5 && redir->type == '<'))
			return (print_sep_error_double(redir->type), -1);
		if (redir->count >= 6 && redir->type == '<')
			return (print_redir_error(), -1);
	}
	if (lst && redir->count >= 1 && is_redir(lst) == 1 \
	&& redir->type != lst->str[0])
		return (msg_syntax_redir(lst));
	if (lst && is_pipe(lst) == 1)
		return (print_single_pipe_error(), -1);
	return (1);
}

t_list	*check_syntax2(t_list *tmp, t_elem *redir)
{
	redir->type = (tmp)->str[0];
	redir->count = 1;
	tmp = tmp->next;
	while (tmp && is_redir(tmp) == 1 && redir->type == tmp->str[0])
	{
		redir->count++;
		tmp = (tmp)->next;
	}
	return (tmp);
}

int	check_syntax(t_data *data, t_list **lst)
{
	t_list	*tmp;
	t_elem	*redir;

	tmp = *lst;
	if (check_first_pipe(tmp) == -1)
		return (g_var = MISUSE_SHELL, -1);
	if (check_last_pipe(lst) == -1)
		return (g_var = MISUSE_SHELL, -1);
	redir = godmalloc(NULL, 0, S_ELEM);
	while (tmp)
	{
		if (is_redir(tmp) == 1)
		{
			tmp = check_syntax2(tmp, redir);
			if (redir->count == 2 && redir->type == '<')
				data->hered_err_mode = 1;
			if (check_syntax3(tmp, redir) == -1)
				return (g_var = MISUSE_SHELL, \
				godmalloc(redir, 0, FREE_PTR), -1);
		}
		if (tmp)
			tmp = tmp->next;
	}	
	return (godmalloc(redir, 0, FREE_PTR), 1);
}
