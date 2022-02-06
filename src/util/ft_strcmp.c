/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 09:02:36 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/14 10:07:15 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	int		ret;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	ret = ft_strncmp(s1, s2, s1_size);
	if (!ret)
		ret = s1_size - s2_size;
	return (ret);
}
