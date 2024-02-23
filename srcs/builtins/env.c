/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 11:36:56 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env **data, char **args)
{
	int			path_line;
	int			j;
	int			nb;

	path_line = varline(data, "PATH");
	nb = get_nb_args_export(args);
	if (path_line == -1)
	{
		write(STDERR_FILENO, ENV_ERR_1, 31);
		g_var = CMD_NOT_FOUND;
	}
	else if (nb != 0)
		write(STDERR_FILENO, ENV_ERR_2, 38);
	else
	{
		j = 0;
		while ((*data)->envp[j])
		{
			write(STDOUT_FILENO, (*data)->envp[j],
				ft_strlen((*data)->envp[j]));
			write(STDOUT_FILENO, "\n", 1);
			++j;
		}
		g_var = EXIT_SUCCESS;
	}
}
