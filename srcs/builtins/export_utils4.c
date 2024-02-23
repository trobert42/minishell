/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:25:34 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 14:41:42 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_size_of_tab(char **tab)
{
	int	cptr;

	cptr = 0;
	if (!tab)
		return (0);
	while (tab[cptr] != NULL)
		cptr++;
	return (cptr);
}

int	is_already_in_cache(t_env **data, t_arg_env arg)
{
	int	i;

	if ((*data)->cache)
	{
		i = 0;
		while (i < get_size_of_tab((*data)->cache))
		{
			if (is_same((*data)->cache[i], arg.name))
				return (1);
			++i;
		}
	}
	return (0);
}

char	**creating_cache(t_arg_env arg)
{
	char	**new_cache;

	new_cache = godmalloc(NULL, 2, TAB_STR);
	new_cache[0] = ft_strdup(arg.name);
	new_cache[1] = NULL;
	return (new_cache);
}

char	**add_export_tab(t_env **data, t_arg_env arg)
{
	int		size;
	char	**new_cache;
	int		i;

	if (is_already_in_cache(data, arg))
		return ((*data)->cache);
	if (varline(data, arg.name) != -1)
		return ((*data)->cache);
	if (!(*data)->cache)
		return (creating_cache(arg));
	size = get_size_of_tab((*data)->cache);
	new_cache = godmalloc(NULL, size + 2, TAB_STR);
	i = -1;
	while ((*data)->cache[++i])
		new_cache[i] = ft_strdup((*data)->cache[i]);
	new_cache[i++] = ft_strdup(arg.name);
	new_cache[i] = NULL;
	i = -1;
	while ((*data)->cache[++i])
		godmalloc((*data)->cache[i], 0, FREE_PTR);
	godmalloc((*data)->cache[i], 0, FREE_PTR);
	godmalloc((*data)->cache, 0, FREE_PTR);
	return (new_cache);
}
