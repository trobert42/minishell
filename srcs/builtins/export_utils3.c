/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:18:14 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/29 16:07:33 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	manage_arg_export_append(t_env **data, t_arg_env *arg)
{
	clean_plus(arg);
	if (arg->name[0] == '\0' && arg->existing == 1)
		return (print_export_4(arg->value));
	else if (uncorrect_var_name_export(arg->name) && arg->existing == 0)
		return (print_export_5(arg->name));
	else if (uncorrect_var_name_export(arg->name))
		return (print_export_6(*arg));
	else if (is_same(arg->name, "_") == 1)
		return (0);
	else if (varline(data, arg->name) == -1 && arg->existing == 1
		&& arg->name[ft_strlen(arg->name) - 1] != ' ')
		add_var_to_env(data, *arg);
	else if (varline(data, arg->name) && arg->existing == 1)
		update_var_to_env_append(data, varline(data, arg->name), *arg);
	return (0);
}

int	get_size_of_export(t_env **data)
{
	int	cptr;

	cptr = 0;
	while ((*data)->envp[cptr])
		cptr++;
	return (cptr);
}

void	ft_swap_export(int **tab, int a, int b)
{
	int	temp;

	temp = (*tab)[a];
	(*tab)[a] = (*tab)[b];
	(*tab)[b] = temp;
}

void	printing_tab_sorted(char **big_tab, int **tab, int env_var_nbr)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (i < env_var_nbr)
	{
		j = 0;
		flag = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (big_tab[(*tab)[i]][j] != '=' && big_tab[(*tab)[i]][j] != '\0')
			write(STDOUT_FILENO, &big_tab[(*tab)[i]][j++], 1);
		if (big_tab[(*tab)[i]][j] == '=')
		{
			write(STDOUT_FILENO, &big_tab[(*tab)[i]][j++], 1);
			flag = printing_tab_sorted_util();
		}
		while (big_tab[(*tab)[i]][j])
			write(STDOUT_FILENO, &big_tab[(*tab)[i]][j++], 1);
		if (flag == 1)
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		++i;
	}
	godmalloc((*tab), 0, FREE_PTR);
}

void	print_env_ascii(t_env **data)
{
	int		*tab;
	int		i;
	int		j;
	int		size;
	char	**big_tab;

	size = get_size_of_export(data) + get_size_of_tab((*data)->cache);
	tab = godmalloc(NULL, size, TAB_INT);
	i = -1;
	while (++i < size)
		tab[i] = i;
	i = -1;
	big_tab = ft_tabjoin((*data)->envp, (*data)->cache);
	while (++i < (size - 1))
	{
		j = i + 1;
		while (j <= (size - 1))
		{
			if (ft_strcmp(big_tab[tab[i]], big_tab[tab[j]]) > 0)
				ft_swap_export(&tab, i, j);
			j ++;
		}
	}
	printing_tab_sorted(big_tab, &tab, size);
	free_split (big_tab);
}
