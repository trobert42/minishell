/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:47:16 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/24 19:31:12 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_no_file_cd(char *str)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, NOENT, 28);
}

void	print_not_dir_cd(char *str)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, NOTDIR, 18);
}

void	print_not_acces_cd(char *str)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, PERM_DENIED, 20);
}

void	print_opt_not_managed_echo(char *str)
{
	write(STDERR_FILENO, "echo: ", 6);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, OPT_NOT_MANAGED, 20);
}

int	print_export_1(char *value)
{
	write(STDERR_FILENO, "export: '=", 10);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, NOT_VALID_ID, 25);
	return (1);
}
