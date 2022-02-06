/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:47:59 by jaejlee           #+#    #+#             */
/*   Updated: 2021/03/10 10:30:43 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len[2];
	char	*s3;

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	s3 = malloc(len[0] + len[1] + 1);
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, len[0] + 1);
	ft_strlcpy(s3 + len[0], s2, len[1] + 1);
	return (s3);
}
