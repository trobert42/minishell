/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:59:25 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_old_pwd(t_env **data, char ***tab)
{
	(*tab) = godmalloc(NULL, 3, TAB_STR);
	(*tab)[0] = ft_strdup("unset");
	(*tab)[1] = ft_strdup("OLDPWD");
	(*tab)[2] = NULL;
	ft_unset(data, *tab);
	godmalloc((*tab)[2], 0, FREE_PTR);
	godmalloc((*tab)[1], 0, FREE_PTR);
	godmalloc((*tab)[0], 0, FREE_PTR);
	godmalloc((*tab), 0, FREE_PTR);
}

void	update_pwd(t_env **data, char ***tab)
{
	(*tab) = godmalloc(NULL, 3, TAB_STR);
	(*tab)[0] = ft_strdup("export");
	(*tab)[1] = ft_strjoin("PWD=", (*data)->pwd);
	(*tab)[2] = NULL;
	ft_export(data, *tab);
	godmalloc((*tab)[2], 0, FREE_PTR);
	godmalloc((*tab)[1], 0, FREE_PTR);
	godmalloc((*tab)[0], 0, FREE_PTR);
	godmalloc((*tab), 0, FREE_PTR);
}

void	update_both_pwd(t_env **data, char ***tab, char *pwd)
{
	(*tab) = godmalloc(NULL, 4, TAB_STR);
	(*tab)[0] = ft_strdup("export");
	(*tab)[1] = ft_strjoin("OLDPWD=", pwd);
	(*tab)[2] = ft_strjoin("PWD=", (*data)->pwd);
	(*tab)[3] = NULL;
	ft_export(data, *tab);
	godmalloc((*tab)[3], 0, FREE_PTR);
	godmalloc((*tab)[2], 0, FREE_PTR);
	godmalloc((*tab)[1], 0, FREE_PTR);
	godmalloc((*tab)[0], 0, FREE_PTR);
	godmalloc((*tab), 0, FREE_PTR);
}

void	update_pwd_old_pwd(t_env **data)
{
	char	**tab;
	char	*pwd;
	char	*oldpwd;

	pwd = get_value_of(data, "PWD");
	oldpwd = get_value_of(data, "OLDPWD");
	tab = NULL;
	if (!pwd && oldpwd)
		unset_old_pwd(data, &tab);
	else if (!oldpwd && pwd)
		update_pwd(data, &tab);
	else if (pwd && oldpwd)
		update_both_pwd(data, &tab, pwd);
	godmalloc(pwd, 0, FREE_PTR);
	godmalloc(oldpwd, 0, FREE_PTR);
}

void	update_env_pwd(t_env **data, char **args)
{
	int		flag;
	char	*tmp;

	flag = 0;
	if ((*data)->pwd)
	{
		if (ft_strlen((*data)->pwd) >= 2 && (*data)->pwd[0] == '/'
			&& (*data)->pwd[1] == '/')
			flag = 1;
	}
	if (ft_strlen(args[1]) == 2 && args[1][0] == '/' && args[1][1] == '/')
		flag = 1;
	tmp = getcwd(NULL, 1024);
	if (!tmp)
		return (getcwd_error());
	if (flag == 1 && args[1])
		double_slash_pwd(data, tmp);
	else
	{
		godmalloc((*data)->pwd, 0, FREE_PTR);
		(*data)->pwd = ft_strdup(tmp);
	}
	free (tmp);
	update_pwd_old_pwd(data);
}
