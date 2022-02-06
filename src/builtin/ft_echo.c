/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 09:54:15 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/28 22:00:09 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int	end_line;

	i = 1;
	if (!argv[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(argv[1], "-n") == 0)
	{
		end_line = 0;
		i++;
	}
	else
		end_line = 1;
	if (argv[i])
		printf("%s", argv[i]);
	while (argv[++i])
		printf(" %s", argv[i]);
	if (end_line)
		printf("\n");
}
