/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	getcmdexecve_size(t_list **tokenlst)
{
	t_list	*lst;
	int		i;

	lst = *tokenlst;
	i = 0;
	while (lst)
	{
		if (lst->type != REDIR_IN && lst->type != REDIR_OUT && lst->type != \
		DIRFILE && lst->type != LIMITER && lst->type != HERE_DOC && lst->type \
		!= APPEND)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**set_cmd_execve(t_list **tokenlst)
{
	t_list	*lst;
	char	**cmd;
	int		size;
	int		i;

	lst = *tokenlst;
	i = 0;
	size = getcmdexecve_size(tokenlst);
	cmd = godmalloc(NULL, size + 1, TAB_STR);
	while (lst)
	{
		if (lst->type != REDIR_IN && lst->type != REDIR_OUT && lst->type != \
		DIRFILE && lst->type != LIMITER && lst->type != HERE_DOC && lst->type \
		!= APPEND)
			cmd[i++] = ft_strdup(lst->str);
		lst = lst->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
