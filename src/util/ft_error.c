/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 09:16:25 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/28 22:37:08 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(t_minishell *ms, char *extra, int errnum, char *msg)
{
	ms->errnum = errnum;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(ms->process, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (extra)
	{
		ft_putstr_fd(extra, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	error_exit(int errnum)
{
	ft_putstr_fd("Error : ", STDERR_FILENO);
	ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(errnum);
}
