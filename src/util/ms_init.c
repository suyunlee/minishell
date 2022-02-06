/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:07:40 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/18 17:10:50 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init(t_minishell *ms, char **envp)
{
	ms->tree = env_to_tree(envp);
	ms->errnum = 0;
	tcgetattr(STDIN_FILENO, &ms->default_term);
	tcgetattr(STDIN_FILENO, &ms->ms_term);
	tree_delete(ms, ms->tree, "OLDPWD");
}
