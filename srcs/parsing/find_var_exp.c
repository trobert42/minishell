/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/07 19:26:10 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_line_nb(t_data *data, char *name)
{
	int	i;
	int	j;
	int	len;
	int	len_line;

	i = 0;
	len = ft_strlen(name);
	while (i < data->env_data->envp_size)
	{
		j = 0;
		len_line = ft_strlen(name);
		while (j < len && j < len_line && \
		name[j] == data->env_data->envp[i][j])
			++j;
		if (name[j] == '\0' && data->env_data->envp[i][j] == '=')
			return (i);
		++i;
	}
	return (-1);
}

char	*find_var_envp(t_data *data, char *var_to_find)
{
	int		j;
	int		index;
	char	*var;

	j = 0;
	index = get_line_nb(data, var_to_find);
	if (index == -1)
		return (NULL);
	else
	{
		while (data->env_data->envp[index][j] != '=')
			j++;
		var = ft_strdup_index(data->env_data->envp[index], \
		j + 1, ft_strlen(data->env_data->envp[index]));
	}
	return (var);
}

int	valid_str_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '=')
			return (1);
	}
	return (0);
}
