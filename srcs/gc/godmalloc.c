/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   godmalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:47:46 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/26 12:28:16 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_malloc_2(int size, enum e_var_type type)
{
	void	*ptr;

	ptr = NULL;
	if (type == S_ELEM)
		ptr = case_s_elem();
	else if (type == S_ELEM_PTR)
		ptr = case_s_elem_ptr();
	else if (type == S_ENV)
		ptr = case_s_env();
	else if (type == S_PIPEX)
		ptr = case_s_pipex();
	else if (type == S_DATA)
		ptr = case_s_data();
	else if (type == S_ARG_ENV)
		ptr = case_s_arg_env(size);
	else if (type == FREE_ALL)
		ptr = NULL;
	return (ptr);
}

void	*ft_malloc(int size, enum e_var_type type)
{
	void	*ptr;

	ptr = NULL;
	if (type == STR)
		ptr = case_str(size);
	else if (type == CHAR)
		ptr = case_char();
	else if (type == TAB_STR)
		ptr = case_tab_str(size);
	else if (type == TAB_INT)
		ptr = case_tab_int(size);
	else if (type == S_LIST)
		ptr = case_s_list();
	else if (type == S_LIST_PTR)
		ptr = case_s_list_ptr();
	else if (type == S_BLOCK)
		ptr = case_s_block();
	else if (type == S_BLOCK_PTR)
		ptr = case_s_block_ptr();
	else
		ptr = ft_malloc_2(size, type);
	return (ptr);
}

void	*petit_liberateur(t_free_list **lst, void **ptr)
{
	t_free_list	*tmp;

	tmp = *lst;
	while ((*lst) != NULL)
	{
		if ((*lst)->ptr == *ptr)
		{
			free((*ptr));
			if ((*lst)->prev && (*lst)->next)
				pl_in_middle(lst);
			else if (!(*lst)->prev && (*lst)->next)
				tmp = pl_in_beggin(lst);
			else if ((*lst)->prev && !(*lst)->next)
				(*lst)->prev->next = NULL;
			else
				tmp = NULL;
			free(*lst);
			break ;
		}
		(*lst) = (*lst)->next;
	}
	put_list_back(lst, tmp);
	return (NULL);
}

void	end_all_malloc_failed(t_free_list **lst)
{
	rl_clear_history();
	free_malloc(lst, NULL, FREE_ALL);
	exit(g_var);
}

void	*godmalloc(void *ptr, int size, enum e_var_type type)
{
	static t_free_list	**lst = NULL;
	void				*ret;

	if (!lst)
	{
		lst = malloc(sizeof(t_free_list *));
		*lst = NULL;
	}
	if (type == FREE_PTR)
		return (petit_liberateur(lst, &ptr));
	if (type == RDL)
		return (godmalloc_readline(lst, ptr, type));
	else
	{
		ret = ft_malloc(size, type);
		if (!ret)
			end_all_malloc_failed(lst);
		else
		{
			if (free_malloc(lst, ret, type) == -1)
				end_all_malloc_failed(lst);
		}
	}
	return (ret);
}
