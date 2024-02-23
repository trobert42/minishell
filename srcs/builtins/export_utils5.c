/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:38:28 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 16:08:16 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_arg_value_util(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

char	*clean_arg_value(char *value)
{
	char	*new_value;
	int		i;
	int		j;

	clean_arg_value_util(&i, &j);
	if (!value)
		return (value);
	new_value = godmalloc(NULL, ft_strlen(value) + 1, STR);
	while (value[i] == ' ')
		++i;
	while (i < ft_strlen(value))
	{
		if (value[i] == ' ')
		{
			new_value[j++] = value[i++];
			if (value[i] == '\0')
				break ;
			while (value[i] == ' ')
				++i;
		}
		new_value[j++] = value[i++];
	}
	new_value[j] = '\0';
	godmalloc(value, 0, FREE_PTR);
	return (new_value);
}

int	printing_tab_sorted_util(void)
{
	write(STDOUT_FILENO, "\"", 1);
	return (1);
}
