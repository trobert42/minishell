/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:13:18 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 15:23:33 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	too_much_args_exit(t_data *data)
{
	if (data->nbr_block == 1)
		write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, EXIT_ERR_1, 25);
	g_var = EXIT_FAILURE;
}

void	numeric_arg_req_exit(t_data *data, char **args)
{
	if (data->nbr_block == 1)
		write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, args[1], ft_strlen(args[1]));
	write(STDERR_FILENO, NUM_ARG_REQ, 28);
	g_var = MISUSE_SHELL;
	if (data->nbr_block == 1)
		godmalloc(NULL, 0, FREE_ALL);
}

void	maj_shlvl(t_env **data)
{
	char	*value;
	char	*new_value;
	int		nb;
	char	**tab;

	value = get_value_of(data, "SHLVL");
	if (!value)
		return ;
	nb = ft_atoi(value);
	nb ++;
	new_value = ft_itoa(nb);
	godmalloc(value, 0, FREE_PTR);
	tab = godmalloc(NULL, 3, TAB_STR);
	tab[0] = ft_strdup("export");
	tab[1] = ft_strjoin("SHLVL=", new_value);
	tab[2] = NULL;
	godmalloc(new_value, 0, FREE_PTR);
	ft_export(data, tab);
	godmalloc(tab[2], 0, FREE_PTR);
	godmalloc(tab[1], 0, FREE_PTR);
	godmalloc(tab[0], 0, FREE_PTR);
	godmalloc(tab, 0, FREE_PTR);
}

int	get_modulo_256_of(unsigned long long int nb, int flag)
{
	int	res;

	if (flag == 0)
		res = nb % 256;
	else
		res = 256 - (nb % 256);
	return (res);
}
