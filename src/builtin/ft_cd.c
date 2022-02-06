/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:27:12 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/15 17:27:12 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_minishell *ms)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_print_error(ms, NULL, EACCES, NULL);
		return (EACCES);
	}
	tree_delete(ms, ms->tree, "OLDPWD");
	tree_insert(ms->tree, tree_init(ft_strdup_g("OLDPWD"), oldpwd));
	return (0);
}

static void	cd_home(t_minishell *ms)
{
	t_tree	*tree;

	tree = tree_get(ms, ms->tree, "HOME", 1);
	if (!tree)
		return ;
	if (update_oldpwd(ms))
		return ;
	if (chdir(tree->value))
		ft_print_error(ms, tree->value, 1, "No such file or directory");
}

static void	cd_oldpwd(t_minishell *ms)
{
	char	*path;
	t_tree	*tree;

	tree = tree_get(ms, ms->tree, "OLDPWD", 1);
	if (!tree)
		return ;
	path = ft_strdup_g(tree->value);
	update_oldpwd(ms);
	if (chdir(path))
		ft_print_error(ms, path, 1, "No such file or directory");
	free(path);
}

void	ft_cd(t_minishell *ms, char **argv)
{
	ms->process = "cd";
	if (!argv[1])
		cd_home(ms);
	else if (ft_strcmp(argv[1], "-") == 0)
		cd_oldpwd(ms);
	else
	{
		update_oldpwd(ms);
		if (chdir(argv[1]))
			ft_print_error(ms, argv[1], 1, "No such file or directory");
	}
	ms->process = "";
}
