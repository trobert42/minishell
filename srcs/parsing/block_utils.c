/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_block(t_block **block)
{
	t_block	*tmp;

	if (!block || !*block)
		return ;
	while ((*block)->next)
	{
		tmp = (*block)->next;
		free_lst2((*block)->tokenlst);
		free_split((*block)->cmd);
		godmalloc((*block)->tokenlst, 0, FREE_PTR);
		godmalloc(*block, 0, FREE_PTR);
		*block = tmp;
	}
	if ((*block)->cmd)
		free_split((*block)->cmd);
	if ((*block)->tokenlst)
	{
		free_lst2((*block)->tokenlst);
		godmalloc((*block)->tokenlst, 0, FREE_PTR);
	}
	godmalloc(*block, 0, FREE_PTR);
	*block = NULL;
}

void	ft_littlelst(t_list **new, t_list *start, t_list *end)
{
	t_list	*tmp1;
	t_list	*tmp;

	*new = godmalloc(NULL, 0, S_LIST);
	tmp1 = *new;
	tmp1->str = ft_strdup(start->str);
	tmp1->type = start->type;
	start = start->next;
	while (start != end)
	{
		tmp = godmalloc(NULL, 0, S_LIST);
		tmp->str = ft_strdup(start->str);
		tmp->type = start->type;
		tmp1->next = tmp;
		tmp1 = tmp;
		start = start->next;
	}
	tmp1->next = NULL;
	set_prev_lst(new);
}

t_block	*ft_blocklast(t_block *block)
{
	if (!block)
		return (0);
	while (block->next != 0)
		block = block->next;
	return (block);
}
