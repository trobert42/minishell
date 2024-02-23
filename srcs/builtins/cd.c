/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:34:36 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	initial_check(char **tab)
{
	int	i;

	i = 1;
	while (tab[i])
		++i;
	if (i > 2)
		return (0);
	return (1);
}

void	cd_too_much_args(void)
{
	write(STDERR_FILENO, CD_ARGS_ERR, 23);
	g_var = EXIT_FAILURE;
}

int	home_check_chdir(t_env **data, char **args)
{
	char	*str;

	if (!args[1])
	{
		str = NULL;
		str = get_value_of(data, "HOME");
		if (!str)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			g_var = EXIT_FAILURE;
			return (-1);
		}
		chdir(str);
		godmalloc(str, 0, FREE_PTR);
	}
	else
		chdir(args[1]);
	if (errno == ENOENT)
		print_no_file_cd(args[1]);
	else if (errno == ENOTDIR)
		print_not_dir_cd(args[1]);
	else if (errno == EACCES)
		print_not_acces_cd(args[1]);
	return (errno);
}

void	double_slash_pwd(t_env **data, char *tmp)
{
	godmalloc((*data)->pwd, 0, FREE_PTR);
	(*data)->pwd = ft_strjoin("/", tmp);
}

void	ft_cd(t_env **data, char **args)
{
	if (!initial_check(args))
		return (cd_too_much_args());
	errno = 0;
	if (home_check_chdir(data, args) == -1)
		return ;
	if (errno != 0)
		g_var = EXIT_FAILURE;
	if (errno != ENOENT && errno != ENOTDIR && errno != EACCES)
		update_env_pwd(data, args);
}
