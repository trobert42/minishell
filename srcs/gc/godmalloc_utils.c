/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_god_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:01:53 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/03 19:02:18 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*case_char(void)
{
	void	*ptr;

	ptr = malloc(sizeof(char));
	return (ptr);
}

void	*case_str(int size)
{
	void	*ptr;

	ptr = malloc(sizeof(char) * size);
	return (ptr);
}

void	*case_tab_str(int size)
{
	void	*ptr;

	ptr = malloc(sizeof(char *) * size);
	return (ptr);
}

void	*case_tab_int(int size)
{
	void	*ptr;

	ptr = malloc(sizeof(int *) * size);
	return (ptr);
}

void	*case_s_list(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_list));
	return (ptr);
}
