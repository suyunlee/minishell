/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 09:33:47 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/18 17:29:12 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_builtin(t_minishell *minishell, char **argv)
{
	minishell->errnum = 0;
	if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(minishell, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(minishell);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(minishell);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(minishell, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(minishell, argv);
	else
		return (1);
	return (0);
}
