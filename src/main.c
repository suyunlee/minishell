/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:11:28 by jaejlee           #+#    #+#             */
/*   Updated: 2021/08/19 11:40:58 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int sig)
{
	pid_t	pid;
	int		statloc;

	pid = waitpid(-1, &statloc, WNOHANG);
	if (sig == SIGINT)
	{
		printf("\n");
		if (pid == -1)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (pid != -1)
		printf("Quit: 3\n");
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	set_echoctl_true(t_minishell *ms)
{
	ms->ms_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &ms->ms_term);
}

static void	set_echoctl_false(t_minishell *ms)
{
	ms->ms_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &ms->ms_term);
}

static int	is_str_empty(char *str)
{
	char	*trimed;

	trimed = ft_strtrim_g(str, " ");
	if (ft_strlen(trimed) == 0)
	{
		free(trimed);
		free(str);
		return (1);
	}
	free(trimed);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	char		*input;

	(void)argc;
	(void)argv;
	ms_init(&ms, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		set_echoctl_false(&ms);
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (is_str_empty(input))
			continue ;
		add_history(input);
		set_echoctl_true(&ms);
		parse_program(&ms, input);
	}
	printf("\x1b[1A\x1b[11C");
	ft_exit(&ms);
}
