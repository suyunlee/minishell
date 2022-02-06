/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:25:16 by jaejlee           #+#    #+#             */
/*   Updated: 2020/12/28 11:48:48 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	src_l;
	size_t	i;

	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	if (dst_l >= size)
		return (src_l + size);
	i = 0;
	while (src[i] && dst_l + i < size - 1)
	{
		dst[dst_l + i] = src[i];
		i++;
	}
	dst[i + dst_l] = 0;
	return (src_l + dst_l);
}
