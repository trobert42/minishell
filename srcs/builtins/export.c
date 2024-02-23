/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:58:06 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg_env	*get_export_vars(char **tab, int nb)
{
	int			i;
	int			k;
	t_arg_env	*arg;
	int			j;

	k = 0;
	arg = godmalloc(NULL, nb + 1, S_ARG_ENV);
	j = 1;
	while (tab[j++])
	{
		arg[k].existing = 0;
		i = 0;
		while (i < ft_strlen(tab[j - 1]) && tab[j - 1][i] != '=')
			++i;
		arg[k].name = ft_strdup_index(tab[j - 1], 0, i);
		if (tab[j - 1][i] == '=')
		{
			arg[k].existing = 1;
			++i;
		}
		arg[k++].value = ft_strdup_index(tab[j - 1], i, ft_strlen(tab[j - 1]));
	}
	arg[k].name = NULL;
	arg[k].value = NULL;
	return (arg);
}

void	update_var_to_env_append(t_env **env_data, int line, t_arg_env arg)
{
	char	*new_var;
	int		i;
	int		j;

	new_var = godmalloc(NULL, ft_strlen((*env_data)->envp[line])
			+ ft_strlen(arg.value) + 1, STR);
	i = 0;
	while ((*env_data)->envp[line][i])
	{
		new_var[i] = (*env_data)->envp[line][i];
		++i;
	}
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

int	uncorrect_var_name_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	if (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		++i;
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		++i;
	}
	return (0);
}

void	clean_plus(t_arg_env *arg)
{
	char	*cleaned;

	cleaned = ft_strdup_index(arg->name, 0, ft_strlen(arg->name) - 1);
	godmalloc(arg->name, 0, FREE_PTR);
	arg->name = cleaned;
}

void	ft_export(t_env **data, char **args)
{
	t_arg_env	*arg;
	int			nb;
	int			k;
	int			ret;

	nb = get_nb_args_export(args);
	if (!nb)
		print_env_ascii(data);
	arg = get_export_vars(args, nb);
	k = -1;
	ret = 0;
	while (arg[++k].name)
	{
		if (ft_strlen(arg[k].name) > 1
			&& arg[k].name[ft_strlen(arg[k].name) - 1] == '+')
			ret += manage_arg_export_append(data, &arg[k]);
		else
			ret += manage_arg_export(data, arg[k]);
	}
	if (ret != 0)
		g_var = EXIT_FAILURE;
	else
		g_var = EXIT_SUCCESS;
	free_arg_struct(arg, nb);
}
