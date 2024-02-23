/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/25 11:33:07 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir(t_list *lst)
{
	if (!lst)
		return (-1);
	if ((is_same_char(lst->str[0], "<>") == 1 && lst->type != VAR && lst->type \
	!= COMMAND) || lst->type == REDIR_IN || lst->type == REDIR_OUT)
		return (1);
	return (-1);
}

int	is_pipe(t_list *lst)
{
	if (!lst)
		return (-1);
	if (is_same_char(lst->str[0], "|") == 1 && lst->type != VAR)
		return (1);
	return (-1);
}

int	msg_syntax_redir(t_list *tmp)
{
	int	count;

	count = 1;
	while (tmp->next && is_redir(tmp->next) == 1 \
	&& tmp->str[0] == tmp->next->str[0])
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 1)
		print_sep_error_simple(tmp->str[0]);
	else if ((count >= 2 && tmp->prev->str[0] == '>') || \
	(count == 2 && tmp->prev->str[0] == '<'))
		print_sep_error_double(tmp->prev->str[0]);
	else if (count >= 3 && tmp->prev->str[0] == '<')
		print_redir_error();
	return (-1);
}
