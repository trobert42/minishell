/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:27:11 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	addtolist(t_list **lst_arg, char *cpy, enum e_wordtype type)
{
	t_list	*tmp;

	ft_lstadd_back(lst_arg, ft_lstnew(cpy));
	tmp = ft_lstlast(*lst_arg);
	tmp->type = type;
}

int	begins_not_dollarquotes(t_data *data, t_elem *e, int i, int j)
{
	while (i < e->len && !is_same_char(e->arg[i], "'\"$"))
		++i;
	if (i != j)
		addtolist(data->lst_arg, ft_strdup_index(e->arg, j, i), UNDEFINED);
	return (i);
}

int	begins_by_quotes(t_data *data, t_elem *e, int i)
{
	if (i < e->len && (e->arg[i] == '\'' || e->arg[i] == '"'))
	{
		e->type = e->arg[i];
		e->index_start = i;
		e->count = 1;
	}
	while (i < e->len && e->count != 2 && e->count != 0)
	{
		i++;
		if (i < e->len && e->arg[i] == e->type)
			ft_quotes(data, e, i++);
	}
	return (i);
}

int	begins_by_tilde(t_data *data, t_list **lst_arg, t_elem *e, int i)
{
	char	*tmp;

	if (e->len == 1 || (e->len >= 2 && e->arg[1] == '/'))
	{
		tmp = find_var_envp(data, "HOME");
		if (!tmp)
			addtolist(lst_arg, ft_strdup(data->env_data->home), DIRFILE);
		else
			addtolist(lst_arg, ft_strdup(tmp), DIRFILE);
		if (tmp)
			godmalloc(tmp, 0, FREE_PTR);
	}
	return (++i);
}

void	ft_parse(t_data *data, t_list **lst_arg, char *old_arg)
{
	int		i;
	int		j;
	t_elem	*elem;

	i = 0;
	elem = godmalloc(NULL, 0, S_ELEM);
	elem->len = ft_strlen(old_arg);
	elem->arg = old_arg;
	while (i < elem->len)
	{
		j = i;
		elem->count = 0;
		elem->str = NULL;
		if (i == 0 && ((elem->len == 1 && old_arg[0] == '~') || \
		(elem->len >= 2 && old_arg[0] == '~' && old_arg[1] == '/')))
			i = begins_by_tilde(data, lst_arg, elem, i);
		else if (i < elem->len && old_arg[i] == '$')
			i = begins_by_dollar(data, elem, i, j);
		else if (i < elem->len && old_arg[i] != '$')
			i = begins_not_dollarquotes(data, elem, i, j);
		i = begins_by_quotes(data, elem, i);
	}
	godmalloc(elem, 0, FREE_PTR);
}
