/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 10:12:39 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/29 09:52:03 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*tree_init(char *key, char *value)
{
	t_tree	*tree;

	tree = malloc_g(sizeof(t_tree));
	tree->parent = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->key = key;
	tree->value = value;
	return (tree);
}

void	tree_insert(t_tree *tree, t_tree *new)
{
	if (ft_strcmp(tree->key, new->key) > 0)
	{
		if (!tree->left)
		{
			tree->left = new;
			new->parent = tree;
		}
		else
			tree_insert(tree->left, new);
	}
	else
	{
		if (!tree->right)
		{
			tree->right = new;
			new->parent = tree;
		}
		else
			tree_insert(tree->right, new);
	}
}

t_tree	*tree_get(t_minishell *ms, t_tree *tree, char *key, int print_error)
{
	int		cmp;
	char	*error;

	if (!tree)
	{
		if (print_error)
		{
			error = ft_strjoin_g(key, " not set");
			ft_print_error(ms, NULL, 1, error);
			free(error);
		}
		return (NULL);
	}
	cmp = ft_strcmp(tree->key, key);
	if (cmp > 0)
		return (tree_get(ms, tree->left, key, print_error));
	if (cmp < 0)
		return (tree_get(ms, tree->right, key, print_error));
	return (tree);
}

void	tree_delete(t_minishell *ms, t_tree *tree, char *key)
{
	t_tree	*delete;
	t_tree	*new;

	delete = tree_get(ms, tree, key, 0);
	if (!delete)
		return ;
	new = NULL;
	if (delete->left)
	{
		new = delete->left;
		if (delete->right)
			tree_insert(new, delete->right);
	}
	else if (delete->right)
		new = delete->right;
	tree = delete->parent;
	if (new)
		new->parent = tree;
	free(delete->key);
	free(delete->value);
	free(delete);
	if (ft_strcmp(tree->key, key) > 0)
		tree->left = new;
	else
		tree->right = new;
}

t_tree	*tree_init_from_line(char *line)
{
	char	*key;
	char	*value;
	char	*temp;

	value = ft_strdup_g(ft_strchr(line, '=') + 1);
	temp = ft_strdup_g(line);
	if (!value || !temp)
		error_exit(ENOMEM);
	*ft_strchr(temp, '=') = '\0';
	key = ft_strdup_g(temp);
	if (!key)
		error_exit(ENOMEM);
	free(temp);
	return (tree_init(key, value));
}
