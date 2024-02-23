/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:55:14 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->env_data->envp_size)
	{
		if (data->env_data->envp[i])
			godmalloc(data->env_data->envp[i], 0, FREE_PTR);
	}
	godmalloc(data->env_data->home, 0, FREE_PTR);
	godmalloc(data->env_data->envp, 0, FREE_PTR);
	godmalloc(data->lst, 0, FREE_PTR);
	godmalloc(data->lst_arg, 0, FREE_PTR);
	godmalloc(data->block, 0, FREE_PTR);
	godmalloc(data->env_data, 0, FREE_PTR);
	godmalloc(data, 0, FREE_PTR);
}
