/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grand_liberateur.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:07:05 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:00:37 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_free_list	*big_lst_new(void *to_add, enum e_var_type flag)
{
	t_free_list	*tmp;

	tmp = malloc(sizeof(t_free_list));
	if (!tmp)
		return (NULL);
	tmp->ptr = to_add;
	tmp->type = flag;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	add_to_big_lst(t_free_list **lst, t_free_list *tmp)
{
	t_free_list	*save;

	if (!(*lst))
		*lst = tmp;
	else
	{
		save = *lst;
		while ((*lst)->next != NULL)
			(*lst) = (*lst)->next;
		tmp->prev = *lst;
		(*lst)->next = tmp;
		*lst = save;
	}
}

t_free_list	*free_list_last(t_free_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	free_big_lst(t_free_list **lst)
{
	t_free_list	*tmp;

	tmp = free_list_last(*lst);
	while (tmp != NULL && tmp != *lst)
	{
		(tmp->prev)->next = NULL;
		free (tmp->ptr);
		free (tmp);
		tmp = free_list_last(*lst);
	}
	if (*lst)
	{
		free((*lst)->ptr);
		free(*lst);
		free(lst);
	}
}

int	free_malloc(t_free_list **lst, void *to_add, enum e_var_type flag)
{
	t_free_list	*tmp;

	if (flag != FREE_ALL)
	{
		tmp = big_lst_new(to_add, flag);
		if (tmp == NULL)
		{
			free_big_lst(lst);
			return (-1);
		}
		add_to_big_lst(lst, tmp);
		return (0);
	}
	else
	{
		free_big_lst(lst);
		return (-1);
	}
}
