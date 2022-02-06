/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:46:57 by jaejlee           #+#    #+#             */
/*   Updated: 2021/07/29 09:52:31 by jaejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_free(int fd, char **memory, char *s1, char *s2)
{
	memory[fd] = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (memory[fd]);
}

static int	read_to_buffer(int fd, char **memory)
{
	char	*buffer;
	ssize_t	len;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	len = read(fd, buffer, BUFFER_SIZE);
	if (len == -1)
		return (-1);
	buffer[len] = '\0';
	if (!memory[fd])
		memory[fd] = buffer;
	else if (!join_free(fd, memory, memory[fd], buffer))
		return (-1);
	if (len)
		return (1);
	return (0);
}

static int	copy_next_line(int fd, char **memory, char **line)
{
	char	*line_end;
	char	*temp;

	line_end = ft_strchr(memory[fd], '\n');
	if (!line_end)
	{
		*line = memory[fd];
		memory[fd] = NULL;
		return (0);
	}
	*line_end = '\0';
	*line = ft_strdup(memory[fd]);
	if (!*line)
		return (-1);
	temp = ft_strdup(line_end + 1);
	if (!temp)
		return (-1);
	free(memory[fd]);
	memory[fd] = temp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*memory[FOPEN_MAX + 1];
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!memory[fd])
	{
		memory[fd] = ft_strdup("");
		if (!memory[fd])
			return (-1);
	}
	ret = 1;
	while (ret && !ft_strchr(memory[fd], '\n'))
	{
		ret = read_to_buffer(fd, memory);
		if (ret == -1)
			return (-1);
	}
	return (copy_next_line(fd, memory, line));
}
