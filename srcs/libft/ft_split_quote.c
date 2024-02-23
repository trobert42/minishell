/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:27:11 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_same_char(char c, char *charset)
{
	int	i;

	i = 0;
	if (!charset)
		return (0);
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	index_cut_end(char *str, int len, int i, char *cs)
{
	t_elem	first_element;

	while (i < len)
	{
		first_element.count = 0;
		if (is_same_char(str[i], cs) == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			first_element.type = str[i];
			first_element.count = 1;
		}
		while (i < len && first_element.count != 2 && first_element.count != 0)
		{
			if (++i < len && str[i] == first_element.type)
				first_element.count++;
		}
		if (++i < len && is_same_char(str[i], cs) == 1)
		{
			i--;
			break ;
		}
	}
	if (first_element.count == 1)
		return (-1);
	return (i);
}

static char	**ft_split2(char *str, int len, char *charset, char **tab)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < len)
	{
		if (is_same_char(str[i], charset) == 1)
		{
			tab[k++] = ft_strdup_index(str, i, i + 1);
			i++;
			continue ;
		}
		j = i;
		i = index_cut_end(str, len, i, charset);
		if (i == -1)
			return (free_all_split(tab, k - 1));
		tab[k] = ft_strdup_index(str, j, ++i);
		if (tab[k] == NULL)
			return (free_all_split(tab, k - 1));
		++k;
	}
	return (tab[k] = 0, tab);
}

char	**ft_split_quote(char *str, char *charset)
{
	char	**tab;
	int		len;

	len = ft_strlen(str);
	if (!str || len == 0)
		return (NULL);
	tab = godmalloc(NULL, len + 1, TAB_STR);
	tab = ft_split2(str, len, charset, tab);
	return (tab);
}
