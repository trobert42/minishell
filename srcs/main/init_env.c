/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/29 15:18:49 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_line_envp(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (*envp != NULL)
	{
		i++;
		if (!*envp++)
			error_free_quit(data, "The env doesn't exist or is NULL\n");
	}
	return (i);
}

char	**get_envp_null(t_data *data)
{
	char	**env_tab;
	char	*pwdstr;

	pwdstr = getcwd(NULL, 1024);
	if (!pwdstr)
		return (write(STDERR_FILENO, "getcwd function has failed\n", 28), NULL);
	data->env_data->envp_size = 3;
	env_tab = godmalloc(NULL, data->env_data->envp_size + 1, TAB_STR);
	env_tab[0] = ft_strjoin("PWD=", pwdstr);
	env_tab[1] = ft_strdup("SHLVL=0");
	env_tab[2] = ft_strdup("_=/usr/bin/env");
	env_tab [3] = NULL;
	free(pwdstr);
	return (env_tab);
}

char	**get_envp(t_data *data, char *envp[])
{
	char	**env_tab;
	int		i;

	if (!*envp)
		env_tab = get_envp_null(data);
	else
	{
		data->env_data->envp_size = count_line_envp(data, envp);
		env_tab = godmalloc(NULL, data->env_data->envp_size + 1, TAB_STR);
		i = -1;
		while (++i < data->env_data->envp_size)
			env_tab[i] = ft_strdup(*envp++);
		env_tab[i] = NULL;
	}
	return (env_tab);
}

char	*get_path_envp(t_data *data, char *envp[])
{
	char	*path_envp;

	(void)data;
	path_envp = NULL;
	while (path_envp == NULL)
	{
		if (!*envp)
			return (NULL);
		path_envp = ft_strnstr(*envp++, "PATH=", 5);
	}
	return (path_envp);
}

char	*get_home_var(t_data *data, char *envp[])
{
	char	*tmp;
	char	*home;

	tmp = NULL;
	(void)data;
	while (tmp == NULL)
	{
		if (!*envp)
			return (NULL);
		tmp = ft_strnstr(*envp++, "HOME=", 5);
	}
	home = ft_strdup_index(tmp, 5, ft_strlen(tmp));
	return (home);
}
