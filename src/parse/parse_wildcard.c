/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:17:52 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/22 11:13:12 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strcmp_wildcard_first(char *wildcard, char *str, char **splited)
{
	int	ret;
	int	temp;

	ret = -1;
	if (wildcard[0] != '*')
	{
		temp = ft_strlen(splited[0]) - ft_strlen(str);
		if (temp > 0 || ft_strncmp(splited[0], str, ft_strlen(splited[0])))
		{
			free_str_arr(splited);
			return (1);
		}
		ret = 0;
	}
	return (ret);
}

static int	strcmp_wildcard(char *wildcard, char *str)
{
	char	**splited;
	int		i;

	splited = ft_split_g(wildcard, '*');
	i = strcmp_wildcard_first(wildcard, str, splited);
	if (i > 0)
		return (1);
	while (splited[++i])
	{
		str = ft_strnstr(str, splited[i], ft_strlen(str));
		if (!str)
		{
			free_str_arr(splited);
			return (1);
		}
		str += ft_strlen(splited[i]);
	}
	free_str_arr(splited);
	if (wildcard[ft_strlen(wildcard) - 1] == '*')
		return (0);
	return (*str);
}

static void	insert_argv(t_cmd *cmd, int index, char *str)
{
	int		len;
	char	**new_argv;
	int		i;

	len = 0;
	while (cmd->argv[len])
		len++;
	new_argv = malloc_g(sizeof(char *) * (len + 2));
	i = -1;
	while (++i < index)
		new_argv[i] = cmd->argv[i];
	new_argv[i] = ft_strdup_g(str);
	while (++i <= len)
		new_argv[i] = cmd->argv[i - 1];
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

static int	free_wildcard(t_minishell *ms, t_cmd *cmd, int index)
{
	int	i;

	if (cmd->index < 1)
		return (0);
	if (strcmp_wildcard(cmd->argv[cmd->index], cmd->argv[cmd->index - 1]) == 0)
	{
		if (cmd->redirect > 0 && cmd->index - index > 1)
		{
			ms->process = cmd->argv[cmd->index];
			ft_print_error(ms, NULL, EPERM, "ambiguous redirect");
			return (1);
		}
		free(cmd->argv[cmd->index--]);
		i = cmd->index;
		while (cmd->argv[++i])
			cmd->argv[i] = cmd->argv[i + 1];
	}
	cmd->index++;
	return (0);
}

int	parse_wildcard(t_minishell *ms, t_cmd *cmd)
{
	DIR				*dir_p;
	char			*path;
	struct dirent	*file;
	int				index;

	path = getcwd(NULL, 0);
	dir_p = opendir(path);
	free(path);
	if (!dir_p)
		error_exit(EPERM);
	file = readdir(dir_p);
	index = cmd->index;
	while (file)
	{
		if (file->d_name[0] != '.' || cmd->argv[cmd->index][0] == '.')
			if (strcmp_wildcard(cmd->argv[cmd->index], file->d_name) == 0)
				insert_argv(cmd, cmd->index++, file->d_name);
		file = readdir(dir_p);
	}
	closedir(dir_p);
	return (free_wildcard(ms, cmd, index));
}
