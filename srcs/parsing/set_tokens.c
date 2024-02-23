/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/24 15:41:11 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign_token_redir(t_list *lst)
{
	if (lst && lst->str[0] == '<' && lst->type != VAR)
	{
		if ((lst->next && lst->next->str[0] == '<' && lst->next->type != VAR) \
		|| (lst->prev && lst->prev->type == HERE_DOC))
			lst->type = HERE_DOC;
		else
			lst->type = REDIR_IN;
	}
	else if (lst && lst->str[0] == '>' && lst->type != VAR)
	{
		if ((lst->next && lst->next->str[0] == '>' && lst->next->type != VAR) \
		|| (lst->prev && lst->prev->type == APPEND))
			lst->type = APPEND;
		else
			lst->type = REDIR_OUT;
	}
}

void	init_tokens_list(t_list **tokenlst)
{
	t_list	*start;
	t_list	*lst;

	lst = *tokenlst;
	start = *tokenlst;
	while (lst)
	{
		if (is_redir(lst) == 1)
			assign_token_redir(lst);
		else if (is_builtin(lst->str) == 1 && is_redir(lst->prev) == -1)
			lst->type = BUILTIN;
		else if (lst->prev && lst->prev->type == HERE_DOC && lst->prev->prev \
		&& lst->prev->prev->type == HERE_DOC)
			lst->type = LIMITER;
		else if (lst->prev && (lst->prev->type == REDIR_IN || lst->prev->type \
		== REDIR_OUT || lst->prev->type == APPEND))
			lst->type = DIRFILE;
		else if (lst == start && is_redir(lst) == -1)
			lst->type = COMMAND;
		lst = lst->next;
	}
}

void	init_first_cmd(t_list **tokenlst)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = *tokenlst;
	while (lst)
	{
		if (is_redir(lst) == -1 && lst->type != DIRFILE && \
		lst->type != LIMITER && lst->type != COMMAND && i == 0 \
		&& lst->prev && lst->prev->type != COMMAND)
		{
			i = 1;
			lst->type = COMMAND;
		}
		lst = lst->next;
	}
}

void	set_tokens_block(t_block **block)
{
	t_block	*b;

	b = *block;
	while (b)
	{
		init_tokens_list(b->tokenlst);
		init_first_cmd(b->tokenlst);
		b->cmd = set_cmd_execve(b->tokenlst);
		b = b->next;
	}
}
