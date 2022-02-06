/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 23:35:17 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/22 10:29:42 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc(t_cmd *cmd)
{
	char	*line;
	int		ret;
	int		fd[2];

	pipe(fd);
	ret = get_next_line(cmd->input_fd, &line);
	while (ret)
	{
		if (ret < 0)
			error_exit(1);
		if (ft_strcmp(line, cmd->eof) == 0)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
		ret = get_next_line(cmd->input_fd, &line);
	}
	free(line);
	cmd->input_fd = fd[0];
	close(fd[1]);
	free(cmd->eof);
}

static int	parse_redirect_in(t_minishell *ms, t_cmd *cmd)
{
	struct stat	s;

	if (cmd->redirect == 1)
	{
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		if (stat(cmd->argv[cmd->index - 1], &s))
		{
			ms->process = cmd->argv[cmd->index - 1];
			ft_print_error(ms, NULL, ENOENT, NULL);
			return (1);
		}
		cmd->input_fd = open(cmd->argv[cmd->index - 1], O_RDONLY);
	}
	else if (cmd->redirect == 2)
	{
		if (cmd->eof)
			free(cmd->eof);
		cmd->eof = ft_strdup_g(cmd->argv[cmd->index - 1]);
		ft_heredoc(cmd);
	}
	return (0);
}

static int	parse_redirect_out(t_minishell *ms, t_cmd *cmd)
{
	int	flag;

	flag = O_RDWR | O_CREAT | O_TRUNC;
	if (cmd->redirect == 3 || cmd->redirect == 4)
	{
		if (cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		if (cmd->redirect == 3 || cmd->redirect == 4)
		{
			if (cmd->redirect == 4)
				flag = O_RDWR | O_CREAT | O_APPEND;
			cmd->output_fd = open(cmd->argv[cmd->index - 1], flag, 0644);
		}
		if (cmd->output_fd < 0)
		{
			ms->process = cmd->argv[cmd->index - 1];
			ft_print_error(ms, NULL, EPERM, "Permission denied");
			return (1);
		}
	}
	return (0);
}

int	get_redirect(t_cmd *cmd, int index)
{
	int	ret;

	ret = 0;
	if (cmd->argv[cmd->index][index] == '<')
		ret = 1;
	else if (cmd->argv[cmd->index][index] == '>')
		ret = 3;
	if (ret && cmd->argv[cmd->index][index + 1] == cmd->argv[cmd->index][index])
	{
		ret++;
		ft_str_del_front(cmd->argv[cmd->index] + index + 1);
	}
	cmd->argv[cmd->index][index] = '\0';
	return (ret);
}

int	parse_redirect(t_minishell *ms, t_cmd *cmd, int new_redirect)
{
	if (cmd->redirect == 0)
	{
		cmd->redirect = new_redirect;
		return (0);
	}
	if (parse_redirect_in(ms, cmd) || parse_redirect_out(ms, cmd))
		return (1);
	cmd->redirect = new_redirect;
	free(cmd->argv[cmd->index - 1]);
	cmd->argv[cmd->index - 1] = cmd->argv[cmd->index];
	cmd->argv[cmd->index--] = NULL;
	return (0);
}
