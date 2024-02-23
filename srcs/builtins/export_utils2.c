/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:42:49 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 10:46:54 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_of(t_env **data, char *name)
{
	char	*value;
	int		i;
	int		line;

	value = NULL;
	line = varline(data, name);
	if (line == -1)
		value = NULL;
	else
	{
		i = 0;
		while ((*data)->envp[line][i] != '=')
			++i;
		value = ft_strdup_index((*data)->envp[line], ++i,
				ft_strlen((*data)->envp[line]));
		value = clean_arg_value(value);
	}
	return (value);
}

int	manage_arg_export(t_env **data, t_arg_env arg)
{
	if (arg.name[0] == '\0' && arg.existing == 1)
		return (print_export_1(arg.value));
	else if (uncorrect_var_name_export(arg.name) && arg.existing == 0)
		return (print_export_2(arg.name));
	else if (uncorrect_var_name_export(arg.name))
		return (print_export_3(arg));
	else if (is_same(arg.name, "_") == 1)
		return (0);
	else if (varline(data, arg.name) == -1 && arg.existing == 1
		&& arg.name[ft_strlen(arg.name) - 1] != ' ')
	{
		add_var_to_env(data, arg);
		(*data)->cache = remove_from_cache(data, arg.name);
	}
	else if (varline(data, arg.name) && arg.existing == 1
		&& new_value(data, varline(data, arg.name), arg.value))
		update_var_to_env(data, varline(data, arg.name), arg);
	else
		(*data)->cache = add_export_tab(data, arg);
	return (0);
}

void	add_var_to_env(t_env **env_data, t_arg_env arg)
{
	char	**new_envp;
	int		i;

	new_envp = envpdup_and_add_var(env_data, arg);
	i = 0;
	while (i <= (*env_data)->envp_size)
	{
		godmalloc((*env_data)->envp[i++], 0, FREE_PTR);
	}
	godmalloc((*env_data)->envp, 0, FREE_PTR);
	(*env_data)->envp = new_envp;
	(*env_data)->envp_size++;
}

void	update_var_to_env(t_env **env_data, int line, t_arg_env arg)
{
	char	*new_var;
	int		i;
	int		j;

	new_var = godmalloc(NULL, ft_strlen(arg.name)
			+ ft_strlen(arg.value) + 2, STR);
	i = 0;
	while (arg.name[i])
	{
		new_var[i] = arg.name[i];
		++i;
	}
	new_var[i++] = '=';
	j = 0;
	while (arg.value[j])
	{
		new_var[i + j] = arg.value[j];
		++j;
	}
	new_var[i + j] = '\0';
	godmalloc((*env_data)->envp[line], 0, FREE_PTR);
	(*env_data)->envp[line] = new_var;
}
