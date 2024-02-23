/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:31:03 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/24 19:31:14 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_export_2(char *name)
{
	write(STDERR_FILENO, "export: '", 9);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, NOT_VALID_ID, 25);
	return (1);
}

int	print_export_3(t_arg_env arg)
{
	write(STDERR_FILENO, "export: '", 9);
	write(STDERR_FILENO, arg.name, ft_strlen(arg.name));
	write(STDERR_FILENO, "=", 1);
	write(STDERR_FILENO, arg.value, ft_strlen(arg.value));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, NOT_VALID_ID, 25);
	return (1);
}

int	print_export_4(char *value)
{
	write(STDERR_FILENO, "export: '+=", 11);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, NOT_VALID_ID, 25);
	return (1);
}

int	print_export_5(char *name)
{
	write(STDERR_FILENO, "export: '", 9);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "+' ", 3);
	write(STDERR_FILENO, NOT_VALID_ID, 25);
	return (1);
}

int	print_export_6(t_arg_env arg)
{
	write(STDERR_FILENO, "export: '", 9);
	write(STDERR_FILENO, arg.name, ft_strlen(arg.name));
	write(STDERR_FILENO, "+=", 2);
	write(STDERR_FILENO, arg.value, ft_strlen(arg.value));
	write(STDERR_FILENO, "' ", 2);
	write(STDERR_FILENO, NOT_VALID_ID, 25);
	return (1);
}
