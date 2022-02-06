/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 09:19:05 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/22 11:09:28 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_child_process(t_minishell *ms, t_cmd *cmd)
{
	char	**envp;
	char	*path;

	ms->process = cmd->argv[0];
	envp = tree_to_env(ms->tree);
	if (cmd->input_fd != STDIN_FILENO)
		dup2(cmd->input_fd, STDIN_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		dup2(cmd->output_fd, STDOUT_FILENO);
	path = find_path(ms, cmd->argv[0]);
	if (ft_strcmp(cmd->argv[0], "exit") && parse_builtin(ms, cmd->argv))
	{
		if (execve(path, cmd->argv, envp))
		{
			ft_print_error(ms, NULL, 127, "command not found");
			exit(127);
		}
	}
	free(path);
	free_str_arr(envp);
	exit(0);
}

static void	update_env(t_minishell *ms, t_cmd *cmd)
{
	t_tree	*new;

	if (!cmd->is_pipe)
	{
		tree_delete(ms, ms->tree, "_");
		new = tree_init(ft_strdup_g("_"), ft_strdup_g(cmd->argv[0]));
		tree_insert(ms->tree, new);
	}
}

static int	fd_close(t_minishell *ms, t_cmd *cmd)
{
	int		statloc;

	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	wait(&statloc);
	ms->errnum = (statloc >> 8) % 256;
	return (ms->errnum);
}

void	parse_program(t_minishell *ms, char *input)
{
	t_cmd	*cmd;
	pid_t	pid;
	t_cmd	*tmp;

	parse_cmd(ms, parse_env(ms, input));
	cmd = ms->cmd_list;
	while (cmd)
	{
		if (parse_argv(ms, cmd))
			return ;
		update_env(ms, cmd);
		if (cmd->is_pipe || parse_builtin(ms, cmd->argv))
		{
			pid = fork();
			if (pid == 0)
				start_child_process(ms, cmd);
			if (fd_close(ms, cmd) && cmd->error_end)
				break ;
		}
		tmp = cmd->next;
		cmd_free(cmd);
		cmd = tmp;
	}
	cmd_lst_free(cmd);
}
