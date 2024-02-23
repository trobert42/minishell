/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:58:15 by dgaloiu           #+#    #+#             */
/*   Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = '\0';
		i++;
	}
}

char	*ft_strdup_index(const char *src, int start, int end)
{
	char	*copy;
	int		size;
	int		i;

	i = 0;
	size = (end - start);
	copy = godmalloc(NULL, size + 1, STR);
	while (i < size)
	{
		copy[i] = src[start + i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strnstr(char *str, char *to_find, int n)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] && i < n && i < ft_strlen(str))
	{
		j = 0;
		start = i;
		while (str[i] == to_find[j] && str[i] != '\0' && i < n)
		{
			i++;
			j++;
		}
		i = start;
		if (to_find[j] == '\0')
			return ((char *)str + start);
		++i;
	}
	return (0);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	minus;
	int	num;

	i = 0;
	minus = 0;
	num = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			++minus;
		++i;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		++i;
	}
	if (minus % 2 == 1)
		num = -num;
	return (num);
}

char	**ft_tabjoin(char **tab1, char **tab2)
{
	char	**res;
	int		i;
	int		j;

	res = godmalloc(NULL,
			get_size_of_tab(tab1) + get_size_of_tab(tab2) + 1, TAB_STR);
	i = 0;
	while (tab1[i])
	{
		res[i] = ft_strdup(tab1[i]);
		++i;
	}
	j = 0;
	if (!tab2)
	{
		res[i] = NULL;
		return (res);
	}
	while (tab2[j])
	{
		res[i + j] = ft_strdup(tab2[j]);
		++j;
	}
	res[i + j] = NULL;
	return (res);
}
