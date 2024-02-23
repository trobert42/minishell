/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:27:11 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_quotes_expand(t_data *data, t_elem *e, int i, int j)
{
	char	*tmp;
	int		k;

	if (e->arg[j] == '$')
		return (addtolist(data->lst_arg, ft_strdup("PID"), VAR), j);
	if (e->arg[j] == '?')
		return (addtolist(data->lst_arg, ft_itoa(data->last_status), VAR), j);
	if (ft_isdigit(e->arg[j]) || is_same_char(e->arg[j], "@-_!*") == 1)
		return (j++);
	k = j;
	while (j < i && ft_isalnum(e->arg[j]) == 1)
		j++;
	tmp = ft_strdup_index(e->arg, k, j);
	e->str = find_var_envp(data, tmp);
	if (e->str)
		addtolist(data->lst_arg, e->str, VAR);
	else
		addtolist(data->lst_arg, ft_strdup(""), VAR);
	godmalloc(tmp, 0, FREE_PTR);
	return (--j);
}

void	ft_quotes(t_data *data, t_elem *e, int i)
{
	int	j;

	j = e->index_start;
	if (i - e->index_start == 2)
		addtolist(data->lst_arg, ft_chardup(e->arg[i - 1]), VAR);
	else if (i == e->index_start + 1)
		addtolist(data->lst_arg, ft_strdup(""), VAR);
	else if ((i - e->index_start > 2 && e->type == '\'') || \
	(check_redir_heredoc(data->lst) == 1))
		addtolist(data->lst_arg, ft_strdup_index(e->arg, \
		e->index_start + 1, i), LIMITER);
	else if (i - e->index_start > 2 && e->type != '\'')
	{
		while (++j < i)
		{
			if ((e->arg[j] == '$' && j + 1 < i && !is_same_char(e->arg[j + 1], \
			"@-_!*$?") && !ft_isalnum(e->arg[j + 1])) || (e->arg[j] != '$') || \
			(e->arg[j] == '$' && j + 1 == i))
				addtolist(data->lst_arg, ft_chardup(e->arg[j]), VAR);
			else if (e->arg[j++] == '$')
				j = ft_quotes_expand(data, e, i, j);
		}
	}
	e->count++;
}

void	begins_by_dollar3(t_data *data, t_elem *e, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup_index(e->arg, j + 1, i);
	e->str = find_var_envp(data, tmp);
	split_export_arg(data, e->str);
	if (e->str)
		addtolist(data->lst_arg, e->str, VAR);
	else if (tmp[0] == '\0')
		addtolist(data->lst_arg, ft_strdup(""), VAR);
	godmalloc(tmp, 0, FREE_PTR);
}

int	begins_by_dollar2(t_data *data, t_elem *e, int i, int j)
{
	if (check_redir_heredoc(data->lst) == 1 && !is_same_char(e->arg[i], "'\""))
	{
		while (i < e->len && !is_same_char(e->arg[i], "'\""))
			++i;
		addtolist(data->lst_arg, ft_strdup_index(e->arg, j, i), LIMITER);
	}
	else
	{
		while (i < e->len && ft_isalnum(e->arg[i]) == 1)
			++i;
		begins_by_dollar3(data, e, i, j);
	}
	return (--i);
}

int	begins_by_dollar(t_data *data, t_elem *e, int i, int j)
{
	++i;
	if (e->len == 1 || e->arg[i] == '\0')
		addtolist(data->lst_arg, ft_strdup("$"), VAR);
	else if (!ft_isalnum(e->arg[i]) && !is_same_char(e->arg[i], "@-_!*$?\"'") \
	&& check_redir_heredoc(data->lst) == -1)
	{
		addtolist(data->lst_arg, ft_strdup("$"), VAR);
		return (i);
	}
	else if (e->arg[i] == '$' && check_redir_heredoc(data->lst) == -1)
		addtolist(data->lst_arg, ft_strdup("PID"), VAR);
	else if (e->arg[i] == '$' && check_redir_heredoc(data->lst) == 1)
		addtolist(data->lst_arg, ft_strdup("$$"), VAR);
	else if (e->arg[i] == '?' && check_redir_heredoc(data->lst) == -1)
		addtolist(data->lst_arg, ft_itoa(data->last_status), VAR);
	else if (ft_isdigit(e->arg[i]))
		return (++i);
	else if (!is_same_char(e->arg[i], "@-_!*"))
		i = begins_by_dollar2(data, e, i, j);
	return (++i);
}
