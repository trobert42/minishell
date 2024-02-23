/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:44:24 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 11:36:29 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_invalid_option(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] != '-')
		return (0);
	++i;
	while (str[i])
	{
		if (str[i] == 'e' || str[i] == 'E')
			flag = 1;
		if (str[i] != 'e' && str[i] != 'E' && str[i] != 'n')
			return (0);
		++i;
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	is_n_option(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 2)
		return (0);
	if (str[i++] != '-')
		return (0);
	while (str[i])
	{
		if (str[i++] != 'n')
			return (0);
	}
	return (1);
}

int	is_not_option(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '-' && str[1] == '\0')
			return (1);
	}
	if (str[i++] != '-')
		return (1);
	while (str[i])
	{
		if (str[i++] != 'n')
			return (1);
	}
	return (0);
}

void	print_echo(char **arg, int i, int printing)
{
	if (printing == 1)
	{
		write(STDOUT_FILENO, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
}

void	ft_echo(char **arg)
{
	int		start_printing;
	int		n;
	int		i;

	n = 0;
	start_printing = 0;
	i = 1;
	while (arg[i])
	{
		if (is_n_option(arg[i]) && start_printing == 0)
			n = 1;
		else if (is_invalid_option(arg[i]) && start_printing == 0)
		{
			print_opt_not_managed_echo(arg[i]);
			break ;
		}
		else if (is_not_option(arg[i]))
			start_printing = 1;
		print_echo(arg, i, start_printing);
		++i;
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	g_var = EXIT_SUCCESS;
}
