/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:32:04 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/19 15:21:44 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_only(t_minishell *ms)
{
	int		i;
	char	**envp;
	char	**splited;

	envp = tree_to_env(ms->tree->right);
	i = -1;
	while (envp[++i])
	{
		splited = ft_split_g(envp[i], '=');
		if (ft_strcmp(splited[0], "_"))
			printf("declare -x %s=\"%s\"\n", splited[0], splited[1]);
		free_str_arr(splited);
	}
	free_str_arr(envp);
}

void	ft_export(t_minishell *minishell, char **argv)
{
	int		i;
	t_tree	*new;

	if (!argv[1])
	{
		export_only(minishell);
		return ;
	}
	i = 0;
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], '='))
			continue ;
		new = tree_init_from_line(argv[i]);
		tree_delete(minishell, minishell->tree, new->key);
		tree_insert(minishell->tree, new);
	}
}
