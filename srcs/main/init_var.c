/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_var(t_data *data, char *envp[])
{
	g_var = 0;
	data->is_var = 0;
	data->nbr_pipe = 0;
	data->env_data = godmalloc(NULL, 0, S_ENV);
	data->env_data->envp = get_envp(data, envp);
	data->env_data->path_envp = get_path_envp(data, envp);
	data->env_data->home = get_home_var(data, envp);
	data->env_data->pwd = get_value_of(&(data->env_data), "PWD");
	data->env_data->cache = NULL;
	data->lst = NULL;
	data->lst = godmalloc(NULL, 0, S_LIST_PTR);
	*data->lst = NULL;
	data->lst_arg = godmalloc(NULL, 0, S_LIST_PTR);
	data->block = godmalloc(NULL, 0, S_BLOCK_PTR);
	*data->block = NULL;
	data->flag_relou = 0;
}
