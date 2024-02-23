/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/26 10:41:23 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_block	*ft_blocknew(t_list *end, t_list *start)
{
	t_block	*new_block;

	new_block = godmalloc(NULL, 0, S_BLOCK);
	new_block->tokenlst = godmalloc(NULL, 0, S_LIST_PTR);
	ft_littlelst(new_block->tokenlst, start, end);
	new_block->cmd = NULL;
	new_block->fd_in = 0;
	new_block->fd_out = 1;
	new_block->fd_hd = -1;
	new_block->hd_name = NULL;
	new_block->next = NULL;
	new_block->prev = NULL;
	return (new_block);
}

int	init_block(t_data *data, t_list *start, t_list *end)
{
	t_block	*new;
	t_block	*tmp;

	if (start == end)
		return (-1);
	new = ft_blocknew(end, start);
	if (!new)
		return (-1);
	if (!*data->block)
	{
		*data->block = new;
		(*data->block)->prev = NULL;
	}
	else
	{
		tmp = ft_blocklast(*data->block);
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}

void	count_nbr_blocks(t_data *data, t_block **block)
{
	int		count;
	t_block	*b;

	count = 0;
	b = *block;
	while (b)
	{
		b->id = count;
		count++;
		b = b->next;
	}
	data->nbr_block = count;
}

void	parse_in_block(t_data *data, t_list **old_lst)
{
	t_list	*start;
	t_list	*tmp;

	tmp = *old_lst;
	start = *old_lst;
	while (*old_lst)
	{
		if (*old_lst && (*old_lst)->type != VAR && (*old_lst)->str[0] == '|')
		{
			init_block(data, start, *old_lst);
			start = (*old_lst)->next;
			data->nbr_pipe++;
		}
		if (*old_lst)
			*old_lst = (*old_lst)->next;
	}
	if (start)
		init_block(data, start, *old_lst);
	set_tokens_block(data->block);
	count_nbr_blocks(data, data->block);
	data->hered_err_mode = 0;
	*old_lst = tmp;
}
