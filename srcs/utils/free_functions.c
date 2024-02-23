/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lst2(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while ((*lst)->next)
	{
		tmp = (*lst)->next;
		godmalloc((*lst)->str, 0, FREE_PTR);
		godmalloc(*lst, 0, FREE_PTR);
		*lst = tmp;
	}
	if ((*lst)->str)
		godmalloc((*lst)->str, 0, FREE_PTR);
	godmalloc(*lst, 0, FREE_PTR);
	*lst = NULL;
}

void	free_lst(t_list *lst)
{
	t_list	*tmp;
	t_list	*start;

	if (!lst)
		return ;
	start = lst;
	while (start->next)
	{
		tmp = start->next;
		godmalloc(start->str, 0, FREE_PTR);
		godmalloc(start, 0, FREE_PTR);
		start = tmp;
	}
	if (start->str)
		godmalloc(start->str, 0, FREE_PTR);
	godmalloc(start, 0, FREE_PTR);
	lst = NULL;
}

void	error_free_quit(t_data *data, char *str)
{
	(void)data;
	write(2, str, ft_strlen(str));
	g_var = EXIT_FAILURE;
	godmalloc(NULL, 0, FREE_ALL);
}

int	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		godmalloc(tab[i++], 0, FREE_PTR);
	godmalloc(tab, 0, FREE_PTR);
	return (0);
}

int	free_int_split(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		godmalloc(tab[i++], 0, FREE_PTR);
	godmalloc(tab, 0, FREE_PTR);
	return (0);
}
