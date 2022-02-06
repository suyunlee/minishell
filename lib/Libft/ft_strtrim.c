/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:07:11 by jaejlee           #+#    #+#             */
/*   Updated: 2021/03/10 10:54:47 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	i;
	size_t	cnt;

	i = ft_strlen(s1);
	cnt = i + 1;
	while (i > 0 && ft_strchr(set, s1[--i]))
		cnt--;
	i = 0;
	while (ft_strchr(set, s1[i++]))
	{
		if (cnt-- == 0)
		{
			ret = malloc(1);
			if (!ret)
				return (NULL);
			ret[0] = '\0';
			return (ret);
		}
	}
	ret = malloc(cnt);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1 + i - 1, cnt);
	return (ret);
}
