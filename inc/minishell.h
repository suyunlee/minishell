/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:20:41 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/22 11:09:19 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# define BUFFER_SIZE 8192

typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	char			*key;
	char			*value;
}	t_tree;

typedef struct s_cmd
{
	struct s_cmd	*next;
	int				input_fd;
	int				output_fd;
	int				pipe[2];
	int				is_pipe;
	char			**argv;
	int				index;
	int				redirect;
	int				quote;
	char			*eof;
	int				error_end;
	int				wildcard_count;
}	t_cmd;

typedef struct s_minishell
{
	t_tree			*tree;
	char			**envp;
	int				errnum;
	char			*process;
	t_cmd			*cmd_list;
	struct termios	default_term;
	struct termios	ms_term;
}	t_minishell;

//builtin
void	ft_cd(t_minishell *ms, char **envp);

void	ft_echo(char **envp);

void	ft_env(t_minishell *minishell);

void	ft_exit(t_minishell *ms);

void	ft_export(t_minishell *minishell, char **envp);

void	ft_pwd(void);

void	ft_unset(t_minishell *minishell, char **envp);

//parse
char	*find_path(t_minishell *minishell, char *program);

int		parse_argv(t_minishell *ms, t_cmd *cmd);

int		parse_builtin(t_minishell *minishell, char **argv);

void	parse_cmd(t_minishell *minishell, char *line);

char	*parse_env(t_minishell *minishell, char *line);

void	parse_program(t_minishell *minishell, char *input);

int		get_redirect(t_cmd *cmd, int index);
int		parse_redirect(t_minishell *ms, t_cmd *cmd, int new_redirect);

int		parse_wildcard(t_minishell *ms, t_cmd *cmd);

//util
t_cmd	*cmd_init(char *cmd);
void	cmd_free(t_cmd *cmd);
void	cmd_lst_free(t_cmd *cmd);

t_tree	*env_to_tree(char **envp);

void	*malloc_g(size_t size);
char	*ft_strdup_g(char *str);
char	*ft_strtrim_g(char const *s1, char const *set);
char	**ft_split_g(char const *s, char c);
char	*ft_strjoin_g(char const *s1, char const *s2);

void	free_str_arr(char **splited);

void	ft_print_error(t_minishell *ms, char *extra, int errnum, char *msg);

void	error_exit(int errnum);

void	ft_str_del_front(char *str);

int		ft_strcmp(char *s1, char *s2);

char	*ft_strjoin3(char *s1, char *s2, char *s3);

int		get_next_line(int fd, char **line);

void	ms_init(t_minishell *ms, char **envp);

char	**tree_to_env(t_tree *tree);

t_tree	*tree_init(char *key, char *value);
void	tree_insert(t_tree *tree, t_tree *new);
t_tree	*tree_get(t_minishell *ms, t_tree *tree, char *key, int print_error);
void	tree_delete(t_minishell *ms, t_tree *tree, char *key);
t_tree	*tree_init_from_line(char *line);

#endif
