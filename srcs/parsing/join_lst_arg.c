/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lst_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:27:11 by trobert           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args_in_lst(t_list **lst)
{
	int		count;
	t_list	*start;

	count = 0;
	start = *lst;
	if (!*lst)
		return (-1);
	while (*lst)
	{
		if ((*lst)->str[0] != '\0')
			count += ft_strlen((*lst)->str);
		*lst = (*lst)->next;
	}
	*lst = start;
	return (count);
}

void	strjoin_arg(char *dest, char *copy)
{
	int	i;
	int	j;
	int	tmp_len;
	int	copy_len;

	i = 0;
	j = 0;
	tmp_len = 0;
	copy_len = ft_strlen(copy);
	if (copy_len == 0)
		return ;
	while (dest[i] != '\0')
		i++;
	tmp_len = i;
	while (i < tmp_len + copy_len)
		dest[i++] = copy[j++];
}

char	*lstjoin_arg(t_list **lst_arg)
{
	char	*new_arg;
	t_list	*start;
	int		new_size;

	start = *lst_arg;
	new_size = count_args_in_lst(lst_arg);
	if (new_size == -1)
		return (NULL);
	if (new_size == 0)
		return (ft_strdup(""));
	new_arg = godmalloc(NULL, new_size + 1, STR);
	ft_bzero(new_arg, new_size);
	while (*lst_arg)
	{
		strjoin_arg(new_arg, (*lst_arg)->str);
		(*lst_arg) = (*lst_arg)->next;
	}
	new_arg[new_size] = '\0';
	*lst_arg = start;
	return (new_arg);
}
