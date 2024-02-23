/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/26 11:58:57 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_same_str(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (0);
	else
	{
		while (i < s1_len)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
	}
	return (1);
}

void	get_limiter_str(t_block *b, t_list *lst)
{
	int		i;
	int		len;

	len = ft_strlen(lst->str);
	b->limiter = godmalloc(NULL, len + 1, STR);
	i = -1;
	while (++i < len)
		b->limiter[i] = lst->str[i];
	b->limiter[i] = '\0';
}

int	is_file(char *pathname, char *cmd)
{
	DIR	*dir;

	dir = opendir(pathname);
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
		{
			if (access(pathname, X_OK | R_OK) == -1)
				print_error_path(pathname, strerror(errno));
			return (g_var = NOT_EXECUTABLE, 1);
		}
		print_error_path(pathname, strerror(errno));
		return (g_var = CMD_NOT_FOUND, 0);
	}
	if (closedir(dir) == 0 && is_same_str(pathname, cmd) == 1)
	{
		write(STDERR_FILENO, pathname, ft_strlen(pathname));
		write(STDERR_FILENO, " : Is a directory\n", 18);
	}
	return (g_var = NOT_EXECUTABLE, 0);
}
