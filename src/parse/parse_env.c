/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 09:29:14 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/20 14:30:20 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_errnum(t_minishell *ms, char *line, int index)
{
	char	*ret;
	char	*errnum;

	errnum = ft_itoa(ms->errnum);
	ft_str_del_front(line + index + 1);
	ret = ft_strjoin3(line, errnum, line + index + 1);
	free(line);
	free(errnum);
	return (ret);
}

static char	*get_key(char *line, int index)
{
	int		i;
	char	*ret;

	i = 1;
	while (ft_isalnum(line[i + index]) || line[i + index] == '_')
		i++;
	ret = malloc_g(sizeof(char) * i);
	i = 0;
	while (ft_isalnum(line[index + 1]) || line[index + 1] == '_')
	{
		ret[i++] = line[index + 1];
		ft_str_del_front(line + index + 1);
	}
	ret[i] = '\0';
	return (ret);
}

static char	*insert_env(t_minishell *ms, char *line, int index)
{
	char	*key;
	char	*ret;
	t_tree	*tree;

	line[index] = '\0';
	if (line[index + 1] == '?')
		return (env_errnum(ms, line, index));
	key = get_key(line, index);
	tree = tree_get(ms, ms->tree, key, 0);
	free(key);
	key = "";
	if (tree)
		key = tree->value;
	if (!tree && !line[index + 1])
		return (line);
	else
		ret = ft_strjoin3(line, key, line + index + 1);
	free(line);
	return (ret);
}

char	*parse_env(t_minishell *minishell, char *line)
{
	int		i;
	int		quote;

	quote = 0;
	i = -1;
	while (line[++i])
	{
		if (quote != 1 && line[i] == '$')
			line = insert_env(minishell, line, i);
		else if (quote != 2 && line[i] == '\'')
			quote = 1 - quote;
		else if (quote != 1 && line[i] == '\"')
			quote = 2 - quote;
	}
	return (line);
}
