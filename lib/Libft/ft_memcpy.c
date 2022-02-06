/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:57:40 by jaejlee           #+#    #+#             */
/*   Updated: 2021/03/10 10:31:00 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dist, const void *src, size_t n)
{
	size_t	i;

	if (!dist && !src)
		return (dist);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dist + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dist);
}
