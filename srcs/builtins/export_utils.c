/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:07:10 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	varline(t_env **data, char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*data)->envp_size)
	{
		j = 0;
		while (j < ft_strlen(name) && j < ft_strlen((*data)->envp[i])
			&& name[j] == (*data)->envp[i][j])
			++j;
		if (name[j] == '\0' && (*data)->envp[i][j] == '=')
			return (i);
		++i;
	}
	return (-1);
}

void	free_arg_struct(t_arg_env *arg, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		godmalloc(arg[i].name, 0, FREE_PTR);
		godmalloc(arg[i].value, 0, FREE_PTR);
		++i;
	}
	godmalloc(arg, 0, FREE_PTR);
}

int	get_nb_args_export(char **arg)
{
	int		nb;
	int		i;

	nb = 0;
	i = 1;
	while (arg[i++])
		nb ++;
	return (nb);
}

char	**envpdup_and_add_var(t_env **data, t_arg_env arg)
{
	char	**new_envp;
	int		i;
	int		j;
	int		k;

	new_envp = godmalloc(NULL, (*data)->envp_size + 2, TAB_STR);
	i = 0;
	while (i < (*data)->envp_size)
	{
		new_envp[i] = ft_strdup((*data)->envp[i]);
		++i;
	}
	new_envp[i] = godmalloc(NULL, ft_strlen(arg.name)
			+ ft_strlen(arg.value) + 2, STR);
	j = -1;
	while (arg.name[++j])
		new_envp[i][j] = arg.name[j];
	new_envp[i][j++] = '=';
	k = -1;
	while (arg.value[++k])
		new_envp[i][j + k] = arg.value[k];
	new_envp[i++][j + k] = '\0';
	new_envp[i] = NULL;
	return (new_envp);
}

int	new_value(t_env **data, int line, char *old_value)
{
	int	i;
	int	j;

	i = 0;
	while ((*data)->envp[line][i] != '=')
	{
		++i;
	}
	++i;
	j = 0;
	while (old_value[j] && (*data)->envp[line][i]
			&& old_value[j] == (*data)->envp[line][i])
	{
		++i;
		++j;
	}
	if (old_value[j] == '\0' && (*data)->envp[line][i] == '\0')
		return (0);
	return (1);
}
