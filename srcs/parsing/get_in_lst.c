/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_clean_arg(t_data *data, char *old_arg)
{
	char	*clean_arg;

	(*data->lst_arg) = NULL;
	if (!old_arg)
		return (NULL);
	ft_parse(data, data->lst_arg, old_arg);
	clean_arg = lstjoin_arg(data->lst_arg);
	if (clean_arg && *data->lst_arg && (*data->lst_arg)->type == VAR)
		data->is_var = 1;
	if (*data->lst_arg)
		free_lst(*data->lst_arg);
	return (clean_arg);
}

int	check_redir_heredoc(t_list **list)
{
	t_list	*last;

	if (!*list)
		return (-1);
	last = ft_lstlast(*list);
	if (last->str[0] == '<' && last->type != VAR)
	{
		if (last->prev && last->prev->str[0] == '<' && last->prev->type != VAR)
			return (1);
	}
	return (-1);
}

void	set_prev_lst(t_list **lst)
{
	t_list	*start;
	t_list	*tmp;

	tmp = NULL;
	if (!*lst)
		return ;
	start = *lst;
	while (*lst)
	{
		(*lst)->prev = tmp;
		tmp = *lst;
		*lst = (*lst)->next;
	}
	*lst = start;
}

void	get_in_lst2(t_data *data, int j, t_list **lst, char **split_ope_tab)
{
	char	*tmp_str;
	t_list	*tmp;

	tmp_str = ft_clean_arg(data, split_ope_tab[j]);
	if (data->flag_relou == 1)
		split_export_arg2(data, tmp_str, lst);
	else if (tmp_str)
	{
		tmp = ft_lstnew(tmp_str);
		ft_lstadd_back(lst, tmp);
		if (((*lst)->next == NULL && data->is_var == 1) || \
		((*lst)->next == NULL && is_same_char((*lst)->str[0], \
		"<>") == 0 && (*lst)->str[0] != '~') || ((*lst)->str[0] == '~' \
		&& ft_strlen((*lst)->str) > 1))
			tmp->type = COMMAND;
		else if (data->is_var == 1)
			tmp->type = VAR;
		else
			tmp->type = UNDEFINED;
	}
	else
		godmalloc(tmp_str, 0, FREE_PTR);
	data->is_var = 0;
	data->flag_relou = 0;
}

int	get_in_lst(t_data *data, char *str, t_list **lst)
{
	char	**split_space_tab;
	char	**split_ope_tab;
	int		i;
	int		j;

	i = -1;
	if (check_sep_error(str) == -1)
		return (g_var = MISUSE_SHELL, -1);
	split_space_tab = ft_split(str, ' ');
	if (!split_space_tab)
		return (-1);
	while (split_space_tab[++i])
	{
		j = -1;
		split_ope_tab = ft_split_quote(split_space_tab[i], "|<>");
		while (split_ope_tab[++j])
			get_in_lst2(data, j, lst, split_ope_tab);
		free_all_split(split_ope_tab, j - 1);
	}
	free_all_split(split_space_tab, i - 1);
	if (!*lst)
		return (g_var = EXIT_SUCCESS, -1);
	return (set_prev_lst(lst), 1);
}
