/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/24 18:10:05 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(t_data *data, char *envp[])
{
	char	*ascii_str1;
	char	*ascii_str2;
	char	*ascii_str3;
	char	*ascii_str4;
	char	*ascii_str5;

	ascii_str1 = "\n  __  __ _       _     _          _ _ \n |  \\/  (_)_ __";
	ascii_str2 = " (_)___| |__   ___| | |\n | |\\/| | | '_ \\| / __| '_ \\ ";
	ascii_str3 = "/ _ \\ | |\n | |  | | | | | | \\__ \\ | | |  __/ | |\n |_|";
	ascii_str4 = "  |_|_|_| |_|_|___/_| |_|\\___|_|";
	ascii_str5 = "_|\n                                      ";
	write(STDERR_FILENO, ascii_str1, 55);
	write(STDERR_FILENO, ascii_str2, 53);
	write(STDERR_FILENO, ascii_str3, 53);
	write(STDERR_FILENO, ascii_str4, 32);
	write(STDERR_FILENO, ascii_str5, 41);
	write(STDERR_FILENO, " \n", 2);
	init_var(data, envp);
}
