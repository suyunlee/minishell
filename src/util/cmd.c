/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 09:05:25 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/22 10:28:04 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_init(char *cmd)
{
	t_cmd	*ret;

	ret = malloc_g(sizeof(t_cmd));
	ret->next = NULL;
	pipe(ret->pipe);
	ret->input_fd = STDIN_FILENO;
	ret->output_fd = STDOUT_FILENO;
	ret->is_pipe = 0;
	ret->redirect = 0;
	ret->eof = NULL;
	ret->argv = malloc_g(sizeof(char *) * 2);
	ret->argv[0] = cmd;
	ret->argv[1] = NULL;
	ret->quote = 0;
	ret->index = 0;
	ret->error_end = 1;
	ret->wildcard_count = 0;
	return (ret);
}

void	cmd_free(t_cmd *cmd)
{
	free_str_arr(cmd->argv);
	free(cmd);
}

void	cmd_lst_free(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd_lst_free(cmd->next);
	cmd_free(cmd);
}
