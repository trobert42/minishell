/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:30:17 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 11:39:30 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_hered_dup_fail2(char *error)
{
	write(STDERR_FILENO, "dup2 for here_fd has failed: ", 30);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, " \n", 2);
}

void	print_redir_error(void)
{
	write(STDERR_FILENO, TOKEN_ERR, 35);
	write(STDERR_FILENO, "`<<<' \n", 7);
}

void	print_single_pipe_error(void)
{
	write(STDERR_FILENO, TOKEN_ERR, 35);
	write(STDERR_FILENO, "`|' \n", 5);
}

void	print_newline_error(void)
{
	write(STDERR_FILENO, TOKEN_ERR, 35);
	write(STDERR_FILENO, "`newline' \n", 11);
}

int	ft_putchar_fd(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}
