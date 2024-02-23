/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_god_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:05:01 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/03 19:05:24 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*case_s_env(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_env));
	return (ptr);
}

void	*case_s_pipex(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_pipex));
	return (ptr);
}

void	*case_s_data(void)
{
	void	*ptr;

	ptr = malloc(sizeof(t_data));
	return (ptr);
}

void	*case_s_arg_env(int size)
{
	void	*ptr;

	ptr = malloc(sizeof(t_arg_env) * size);
	return (ptr);
}
