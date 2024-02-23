/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_god_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:03:50 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/03 19:04:09 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*case_s_list_ptr(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_list *));
	return (ptr);
}

void	*case_s_block(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_block));
	return (ptr);
}

void	*case_s_block_ptr(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_block *));
	return (ptr);
}

void	*case_s_elem(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_elem));
	return (ptr);
}

void	*case_s_elem_ptr(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_elem *));
	return (ptr);
}
