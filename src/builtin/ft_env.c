/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 09:35:27 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/28 15:10:08 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell)
{
	int		i;
	char	**env;

	env = tree_to_env(minishell->tree->right);
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	free_str_arr(env);
}
