/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:58:29 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/29 09:41:19 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*env_to_tree(char **envp)
{
	t_tree	*tree;
	int		i;

	tree = tree_init(ft_strdup_g(""), ft_strdup_g(""));
	i = -1;
	while (envp[++i])
		tree_insert(tree, tree_init_from_line(envp[i]));
	return (tree);
}
