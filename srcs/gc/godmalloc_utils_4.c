/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   godmalloc_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:48:10 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/26 12:27:31 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pl_in_middle(t_free_list **lst)
{
	(*lst)->prev->next = (*lst)->next;
	(*lst)->next->prev = (*lst)->prev;
}

t_free_list	*pl_in_beggin(t_free_list **lst)
{
	t_free_list	*tmp;

	(*lst)->next->prev = NULL;
	tmp = (*lst)->next;
	return (tmp);
}

void	put_list_back(t_free_list **lst, t_free_list *tmp)
{
	if (!tmp)
	{	
		free(lst);
		lst = NULL;
	}
	else
		*lst = tmp;
}

void	*godmalloc_readline(t_free_list **lst, void *ptr, enum e_var_type type)
{
	if (free_malloc(lst, ptr, type) == -1)
		end_all_malloc_failed(lst);
	return (NULL);
}
