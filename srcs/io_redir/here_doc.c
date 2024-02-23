/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/29 14:01:54 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc_expand(t_data *data, char *str, int fd, int i)
{
	char	*tmp;
	char	*var;
	int		len;
	int		j;

	len = ft_strlen(str);
	i++;
	j = i;
	while (i < len && !is_same_char(str[i], "$\" '\n"))
		i++;
	tmp = ft_strdup_index(str, j, i);
	var = find_var_envp(data, tmp);
	if (var)
		write(fd, var, ft_strlen(var));
	godmalloc(tmp, 0, FREE_PTR);
	godmalloc(var, 0, FREE_PTR);
	--i;
	return (i);
}

int	expand_pid_or_gvar(char *str, int len, int fd, int i)
{
	if (i + 1 < len && str[i + 1] == '$')
	{
		i++;
		write(fd, "PID", 3);
	}
	else if (i + 1 < len && str[i + 1] == '?')
	{
		i++;
	}
	return (i);
}

void	here_doc_putstr(t_data *data, char *str, int len, int fd)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		while (i < len && str[i] != '$')
			ft_putchar_fd(fd, str[i++]);
		if (i < len && str[i] == '$')
		{
			if ((i + 1 < len && is_same_char(str[i + 1], "\"'{}()\n ") == 1) \
			|| (i + 1 == len))
				ft_putchar_fd(fd, str[i]);
			else if ((i + 1 < len && str[i + 1] == '$') || \
			(i + 1 < len && str[i + 1] == '?'))
				i = expand_pid_or_gvar(str, len, fd, i);
			else
				i = here_doc_expand(data, str, fd, i);
		}
	}
	ft_putchar_fd(fd, '\n');
}

void	hered_mode_gnl(t_data *data, int fd, char *limiter)
{
	char	*str;
	char	len;

	str = NULL;
	g_var = EXIT_SUCCESS;
	while (1)
	{
		str = readline("> ");
		godmalloc(str, 0, RDL);
		if (!str)
		{
			write(STDIN_FILENO, HDEOF_ERR, 48);
			break ;
		}
		if (is_same_str(str, limiter) == 1)
		{
			godmalloc(str, 0, FREE_PTR);
			g_var = EXIT_SUCCESS;
			break ;
		}
		len = ft_strlen(str);
		here_doc_putstr(data, str, len, fd);
		godmalloc(str, 0, FREE_PTR);
	}
	godmalloc(limiter, 0, FREE_PTR);
}

int	hered_mode(t_data *data, t_block *b)
{
	hered_mode_gnl(data, b->fd_in, b->limiter);
	b->fd_hd = b->fd_in;
	return (1);
}
