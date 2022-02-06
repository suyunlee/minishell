/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_guard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 09:38:11 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/29 14:58:28 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*malloc_g(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		error_exit(ENOMEM);
	return (ret);
}

char	*ft_strdup_g(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	if (!ret)
		error_exit(ENOMEM);
	return (ret);
}

char	*ft_strtrim_g(char const *s1, char const *set)
{
	char	*ret;

	ret = ft_strtrim(s1, set);
	if (!ret)
		error_exit(ENOMEM);
	return (ret);
}

char	**ft_split_g(char const *s, char c)
{
	char	**ret;

	ret = ft_split(s, c);
	if (!ret)
		error_exit(ENOMEM);
	return (ret);
}

char	*ft_strjoin_g(char const *s1, char const *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		error_exit(ENOMEM);
	return (ret);
}
