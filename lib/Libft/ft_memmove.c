/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:27:28 by jaejlee           #+#    #+#             */
/*   Updated: 2021/03/10 10:57:35 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	tmp;

	if (dst == src || len == 0)
		return (dst);
	i = 0;
	while (i < len)
	{
		if (dst < src)
			tmp = i;
		else
			tmp = len - i - 1;
		*(unsigned char *)(dst + tmp) = *(unsigned char *)(src + tmp);
		i++;
	}
	return (dst);
}
