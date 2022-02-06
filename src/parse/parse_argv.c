/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 20:16:20 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/22 11:02:31 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_new_argv(t_cmd *cmd, int index)
{
	int		i;
	char	*temp;
	char	**new_argv;

	i = 0;
	while (cmd->argv[i])
		i++;
	new_argv = malloc_g(sizeof(char *) * (i + 2));
	i = -1;
	while (cmd->argv[++i])
		new_argv[i] = cmd->argv[i];
	temp = new_argv[i - 1];
	new_argv[i - 1] = ft_strdup_g(temp);
	new_argv[i] = ft_strtrim_g(temp + index + 1, " ");
	new_argv[i + 1] = NULL;
	free(temp);
	return (new_argv);
}

static int	add_arg(t_minishell *ms, t_cmd *cmd, int index)
{
	char	*temp;
	char	**new_argv;

	if (index == 0)
	{
		temp = cmd->argv[cmd->index];
		cmd->argv[cmd->index] = ft_strtrim_g(temp + 1, " ");
		free(temp);
		return (0);
	}
	new_argv = get_new_argv(cmd, index);
	free(cmd->argv);
	cmd->argv = new_argv;
	if (cmd->redirect != 2 && ft_strchr(cmd->argv[cmd->index], '*'))
		return (parse_wildcard(ms, cmd));
	cmd->index++;
	return (0);
}

static void	parse_quote(t_cmd *cmd, int *index_p)
{
	if (cmd->quote != 2 && cmd->argv[cmd->index][*index_p] == '\'')
	{
		cmd->quote = 1 - cmd->quote;
		ft_str_del_front(cmd->argv[cmd->index] + (*index_p)--);
	}
	else if (cmd->quote != 1 && cmd->argv[cmd->index][*index_p] == '\"')
	{
		cmd->quote = 2 - cmd->quote;
		ft_str_del_front(cmd->argv[cmd->index] + (*index_p)--);
	}
}

int	parse_argv(t_minishell *ms, t_cmd *cmd)
{
	int		i;
	int		new_redirect;

	i = -1;
	while (cmd->argv[cmd->index][++i])
	{
		if (cmd->quote == 0 && ft_strchr(" <>", cmd->argv[cmd->index][i]))
		{
			new_redirect = get_redirect(cmd, i);
			if (add_arg(ms, cmd, i) || parse_redirect(ms, cmd, new_redirect))
				return (1);
			i = -1;
		}
		else
			parse_quote(cmd, &i);
	}
	if (cmd->redirect != 2 && ft_strchr(cmd->argv[cmd->index], '*'))
		return (parse_wildcard(ms, cmd));
	if (cmd->redirect)
	{
		cmd->index++;
		return (parse_redirect(ms, cmd, 0));
	}
	return (0);
}
