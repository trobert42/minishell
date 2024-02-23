/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sep_in_words(char *str, int start, int end)
{
	while (start <= end)
	{
		if (is_same_char(str[start], "|&<>"))
			return (1);
		start++;
	}
	return (0);
}

void	split_export_arg2(t_data *data, char *tmp_str, t_list **lst)
{
	char	**tab;
	t_list	*tmp;
	int		i;

	i = 0;
	(void)data;
	tab = ft_split(tmp_str, ' ');
	while (tab[i])
	{
		tmp = ft_lstnew(tab[i]);
		ft_lstadd_back(lst, tmp);
		i++;
	}
	i = 0;
	godmalloc(tab, 0, FREE_PTR);
}

void	split_export_arg(t_data *data, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == ' ')
			data->flag_relou = 1;
		i++;
	}
}
