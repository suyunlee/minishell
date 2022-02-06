/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 09:08:30 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/19 12:42:43 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_minishell *ms, char *program)
{
	char		**path;
	struct stat	s;
	int			i;
	char		*ret;
	t_tree		*tree;

	tree = tree_get(ms, ms->tree, "PATH", 0);
	if (!tree)
		return (NULL);
	path = ft_split_g(tree->value, ':');
	i = -1;
	while (path[++i])
	{
		ret = ft_strjoin3(path[i], "/", program);
		if (!stat(ret, &s))
			break ;
		free(ret);
	}
	if (!path[i])
		ret = ft_strdup_g(program);
	free_str_arr(path);
	return (ret);
}
