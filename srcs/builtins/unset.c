/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:33:03 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 14:56:11 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**envpdup_delete_var(t_env **env_data, int line)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = godmalloc(NULL, (*env_data)->envp_size, TAB_STR);
	i = 0;
	j = 0;
	while (i < (*env_data)->envp_size)
	{
		if (i != line)
			new_envp[j++] = ft_strdup((*env_data)->envp[i]);
		++i;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

int	unset_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		++i;
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

void	get_return_value_export(int ret)
{
	if (ret != 0)
		g_var = EXIT_FAILURE;
	else
		g_var = EXIT_SUCCESS;
}

char	**remove_from_cache(t_env **data, char *str)
{
	char	**new_cache;
	int		i;
	int		j;

	if (!(*data)->cache)
		return (NULL);
	if ((*data)->cache[0] == NULL)
		return (NULL);
	new_cache = godmalloc(NULL, get_size_of_tab((*data)->cache), TAB_STR);
	i = 0;
	j = 0;
	while (i < get_size_of_tab((*data)->cache))
	{
		if (!is_same(str, (*data)->cache[i]))
			new_cache[j++] = ft_strdup((*data)->cache[i]);
		++i;
	}
	if (get_size_of_tab((*data)->cache) != 0)
		new_cache[j] = NULL;
	i = 0;
	while (i < get_size_of_tab((*data)->cache))
		godmalloc((*data)->cache[i++], 0, FREE_PTR);
	godmalloc((*data)->cache[i], 0, FREE_PTR);
	godmalloc((*data)->cache, 0, FREE_PTR);
	return (new_cache);
}

void	ft_unset(t_env **data, char **args)
{
	int		j;
	int		i;
	char	**new_envp;
	int		ret;

	j = 0;
	ret = 0;
	while (args[++j])
	{
		if (unset_arg(args[j]) && varline(data, args[j]) != -1)
		{
			new_envp = envpdup_delete_var(data, varline(data, args[j]));
			(*data)->cache = remove_from_cache(data, args[j]);
			i = 0;
			while (i <= (*data)->envp_size)
				godmalloc((*data)->envp[i++], 0, FREE_PTR);
			godmalloc((*data)->envp, 0, FREE_PTR);
			(*data)->envp = new_envp;
			(*data)->envp_size--;
		}
		else if (!unset_arg(args[j]))
			ret = 1;
	}
	get_return_value_export(ret);
}
