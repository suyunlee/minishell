/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 10:34:17 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/20 09:09:33 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*cmd_insert(t_cmd *cmd, int index)
{
	t_cmd	*new;
	char	*temp;

	temp = cmd->argv[0];
	new = cmd_init(ft_strtrim_g(temp + index + 1, " "));
	if (cmd->argv[0][index] == cmd->argv[0][index + 1])
	{
		ft_str_del_front(new->argv[0]);
		if (cmd->argv[0][index] == '|')
			cmd->error_end = 0;
	}
	else if (cmd->argv[0][index] == '|')
	{
		cmd->output_fd = cmd->pipe[1];
		new->input_fd = cmd->pipe[0];
		cmd->is_pipe = 1;
		new->is_pipe = 1;
	}
	temp[index] = '\0';
	cmd->argv[0] = ft_strtrim_g(temp, " ");
	free(temp);
	cmd->next = new;
	return (new);
}

void	parse_cmd(t_minishell *minishell, char *line)
{
	int		i;
	int		quote;
	t_cmd	*cmd;

	cmd = cmd_init(line);
	minishell->cmd_list = cmd;
	quote = 0;
	i = -1;
	while (cmd->argv[0][++i])
	{
		if (quote == 0 && (cmd->argv[0][i] == '&' || cmd->argv[0][i] == '|'))
		{
			cmd = cmd_insert(cmd, i);
			i = -1;
		}
		else if (quote != 2 && cmd->argv[0][i] == '\'')
			quote = 1 - quote;
		else if (quote != 1 && cmd->argv[0][i] == '\"')
			quote = 2 - quote;
	}
}
