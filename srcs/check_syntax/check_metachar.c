/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/24 18:43:31 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_sep_error2(char *str, int i, t_elem elem)
{
	t_elem	sep;
	int		j;

	if (is_same_char(str[i], "`&#*!;\\()[]"))
		return (write(STDERR_FILENO, "metachar not managed\n", 21), -1);
	if (is_same_char(str[i], "<>|"))
	{
		sep.type = str[i];
		++i;
		j = i;
		while (i < elem.len && str[i] == ' ')
			++i;
		if (i < elem.len && str[i] == sep.type && j != i && i + 1 < elem.len \
		&& str[i + 1] == sep.type)
			return (print_sep_error_double(sep.type), -1);
		else if (i < elem.len && str[i] == sep.type && j != i)
			return (print_sep_error_simple(sep.type), -1);
	}
	++i;
	return (0);
}

int	check_sep_error(char *str)
{
	int		i;
	t_elem	elem;

	i = 0;
	elem.len = ft_strlen(str);
	elem.count = 0;
	while (i < elem.len)
	{
		if (i < elem.len && (str[i] == '\'' || str[i] == '"'))
		{
			elem.type = str[i];
			elem.index_start = i;
			elem.count = 1;
		}
		while (i < elem.len && elem.count != 2 && elem.count != 0)
		{
			++i;
			if (str[i] == elem.type)
				elem.count = 0;
		}
		if (check_sep_error2(str, i, elem) == -1)
			return (-1);
		++i;
	}
	return (0);
}
