/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:19:44 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/04 17:30:57 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_row(char *str, char c)
{
	int	last;
	int	size;

	last = 1;
	size = 0;
	while (*str)
	{
		if (last && *str != c)
			size++;
		last = *(str++) == c;
	}
	return (size);
}

static char	**free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static char	**get_column(char **strs, char *str, char c)
{
	int	i;
	int	j;
	int	last;

	i = 0;
	last = 1;
	while (*str)
	{
		if (last && !(*str == c))
		{
			j = 0;
			while (*str && !(*(str++) == c))
				j++;
			str--;
			strs[i] = malloc(j + 1);
			if (!strs[i++])
				return (free_split(strs));
		}
		if (*str)
			last = *(str++) == c;
	}
	return (strs);
}

static void	set_column(char **strs, char *str, char c)
{
	int	i;
	int	j;
	int	last;

	i = 0;
	last = 1;
	while (*str)
	{
		if (last && !(*str == c))
		{
			j = 0;
			while (*str && !(*str == c))
				strs[i][j++] = *str++;
			strs[i++][j] = 0;
		}
		if (*str)
			last = *(str++) == c;
	}
	strs[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**strs;
	int		size;

	str = (char *)s;
	size = get_row(str, c);
	strs = malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (NULL);
	if (!get_column(strs, str, c))
		return (NULL);
	set_column(strs, str, c);
	return (strs);
}
