/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:19:05 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/18 17:28:59 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_minishell *minishell, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		tree_delete(minishell, minishell->tree, argv[i]);
}
