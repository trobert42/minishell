/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:30:32 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/24 19:30:46 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_path(char *path, char *error)
{
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, " \n", 2);
}

void	print_sep_error_double(char c)
{
	write(STDERR_FILENO, TOKEN_ERR, 35);
	write(STDERR_FILENO, "`", 1);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "' \n", 3);
}

void	print_sep_error_simple(char c)
{
	write(STDERR_FILENO, TOKEN_ERR, 35);
	write(STDERR_FILENO, "`", 1);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "' \n", 3);
}

void	print_hered_fail(char *error)
{
	write(STDERR_FILENO, "can't create temp file for here document: ", 42);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, " \n", 2);
}

void	print_hered_dup_fail(char *error)
{
	write(STDERR_FILENO, "dup2 for here_fd has failed: ", 29);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, " \n", 2);
}
