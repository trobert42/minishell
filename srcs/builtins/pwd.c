/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:17:09 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env **data)
{
	char	*pwdstr;
	char	*str;

	pwdstr = getcwd(NULL, 1024);
	if (pwdstr == NULL)
	{
		str = get_value_of(data, "PWD");
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
		godmalloc(str, 0, FREE_PTR);
		return ;
	}
	if (ft_strlen((*data)->pwd) >= 2
		&& (*data)->pwd[0] == '/' && (*data)->pwd[1] == '/')
	{
		write(STDOUT_FILENO, "/", 1);
		write(STDOUT_FILENO, pwdstr, ft_strlen(pwdstr));
	}
	else
		write(STDOUT_FILENO, pwdstr, ft_strlen(pwdstr));
	write(STDOUT_FILENO, "\n", 1);
	free (pwdstr);
	g_var = EXIT_SUCCESS;
}
