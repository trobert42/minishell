/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:27:11 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_all_split(char **tab, int k)
{
	while (k >= 0)
	{
		if (tab[k])
			godmalloc(tab[k], 0, FREE_PTR);
		k--;
	}
	if (tab)
		godmalloc(tab, 0, FREE_PTR);
	return (NULL);
}

static int	index_cut_end(char *str, int len, int i, char c)
{
	t_elem	first_element;

	while (i < len)
	{
		first_element.count = 0;
		if (str[i] != c && (str[i] == '\'' || str[i] == '"'))
		{
			first_element.type = str[i];
			first_element.count = 1;
		}
		while (i < len && first_element.count != 2 && first_element.count != 0)
		{
			i++;
			if (i < len && str[i] == first_element.type)
				first_element.count++;
		}
		i++;
		if (i < len && str[i] == c)
			break ;
	}
	if (first_element.count == 1)
		return (-1);
	return (i);
}

static char	**ft_split2(char *str, int len, char c, char **tab)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < len)
	{
		while (i < len && str[i] == c)
			++i;
		j = i;
		if (!str[i])
			break ;
		i = index_cut_end(str, len, i, c);
		if (i == -1)
			return (free_all_split(tab, k - 1));
		tab[k] = ft_strdup_index(str, j, i++);
		if (tab[k] == NULL)
			return (free_all_split(tab, k - 1));
		++k;
	}
	tab[k] = 0;
	return (tab);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	int		len;

	len = ft_strlen(str);
	if (!str || len == 0)
		return (NULL);
	tab = godmalloc(NULL, len + 1, TAB_STR);
	tab = ft_split2(str, len, c, tab);
	if (!tab)
	{
		write(STDERR_FILENO, "odd quotes parsing error\n", 25);
		g_var = MISUSE_SHELL;
	}
	return (tab);
}
