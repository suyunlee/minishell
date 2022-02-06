/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:29:33 by jaejlee           #+#    #+#             */
/*   Updated: 2020/12/26 21:17:32 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)*(s1 + i) > (unsigned char)*(s2 + i))
			return (1);
		else
		{
			if ((unsigned char)*(s1 + i) < (unsigned char)*(s2 + i))
				return (-1);
		}
		if (!*(s1 + i) || !*(s2 + i))
			return (0);
		i++;
	}
	return (0);
}
