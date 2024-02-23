/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_last_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:33:48 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/24 17:26:10 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_last_pipe(t_list **lst_arg)
{
	t_list	*lst;

	lst = ft_lstlast(*lst_arg);
	if (is_pipe(lst) == 1)
	{
		write(STDERR_FILENO, "last pipe specific case not managed\n", 36);
		return (-1);
	}
	return (1);
}

int	check_first_pipe(t_list *lst)
{
	if (lst && is_pipe(lst) == 1)
	{
		if (lst->next && is_pipe(lst->next) == 1)
		{
			write(STDERR_FILENO, TOKEN_ERR, 35);
			write(STDERR_FILENO, "`||' \n", 6);
		}
		else
		{
			write(STDERR_FILENO, TOKEN_ERR, 35);
			write(STDERR_FILENO, "`|' \n", 5);
		}
		return (-1);
	}
	return (1);
}
