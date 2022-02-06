/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 22:04:25 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/04 17:34:57 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(long long n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t		len;
	long long	num;
	char		*ret;

	num = n;
	len = get_len(num);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len--] = '\0';
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	if (n < 0)
		num *= -1;
	while (num > 0)
	{
		ret[len--] = num % 10 + '0';
		num /= 10;
	}
	if (len == 0)
		ret[0] = '-';
	return (ret);
}
