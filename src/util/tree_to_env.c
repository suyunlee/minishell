/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:39:38 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/29 09:47:51 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**merge_env(t_tree *tree, char **env_left, char **env_right)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	while (env_left[i])
		i++;
	j = 0;
	while (env_right[j])
		j++;
	env = malloc_g(sizeof(char *) * (i + j + 2));
	i = -1;
	while (env_left[++i])
		env[i] = env_left[i];
	env[i++] = ft_strjoin3(tree->key, "=", tree->value);
	j = 0;
	while (env_right[j])
		env[i++] = env_right[j++];
	env[i] = NULL;
	free(env_left);
	free(env_right);
	return (env);
}

char	**tree_to_env(t_tree *tree)
{
	char	**env;

	if (!tree)
	{
		env = malloc_g(sizeof(char *));
		env[0] = NULL;
		return (env);
	}
	env = merge_env(tree, tree_to_env(tree->left), tree_to_env(tree->right));
	return (env);
}
