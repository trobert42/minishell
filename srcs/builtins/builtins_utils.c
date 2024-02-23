/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:47:17 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/13 15:20:11 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_same(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i])
	{
		++i;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (is_same(str, "echo") || is_same(str, "cd") || is_same(str, "pwd")
		|| is_same(str, "export") || is_same(str, "unset")
		|| is_same(str, "env") || is_same(str, "exit"))
		return (1);
	return (0);
}
