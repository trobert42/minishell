/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:21:43 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 15:36:53 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned long long int	ft_atoull(char *nptr, int *flag)
{
	int						i;
	unsigned long long int	num;

	i = 0;
	num = 0;
	*flag = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			*flag = 1;
		++i;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		++i;
	}
	return (num);
}

int	get_nb_args_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

int	is_num_arg(char *str)
{
	unsigned long long int	n;
	int						i;
	int						j;

	j = 0;
	if (ft_strlen(str) > 20 || (ft_strlen(str) == 20 && str[0] != '-'))
		return (0);
	n = ft_atoull(str, &i);
	if (str[0] == '+' || str[0] == '-')
		++j;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (0);
		++j;
	}
	if (n <= 9223372036854775807
		|| is_same("-9223372036854775808", str) == 1)
		return (1);
	return (0);
}

void	exit_one_num_arg(t_data *data, char **args)
{
	int					i;
	unsigned long long	nb;

	nb = ft_atoull(args[1], &i);
	g_var = get_modulo_256_of(nb, i);
	if (data->nbr_block == 1)
	{
		write(STDERR_FILENO, "exit\n", 5);
		close_saved_dup(data);
		godmalloc(NULL, 0, FREE_ALL);
	}
}

void	ft_exit(t_data *data, char **args)
{
	if (get_nb_args_exit(args) > 2 && is_num_arg(args[1]))
		return (too_much_args_exit(data));
	else if (get_nb_args_exit(args) == 1)
	{
		g_var = data->last_status;
		if (data->nbr_block == 1)
		{
			write(STDERR_FILENO, "exit\n", 5);
			close_saved_dup(data);
			godmalloc(NULL, 0, FREE_ALL);
		}
	}
	else if (!is_num_arg(args[1]))
		numeric_arg_req_exit(data, args);
	else if (is_num_arg(args[1]))
		exit_one_num_arg(data, args);
}
