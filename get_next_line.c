/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:57:08 by huates            #+#    #+#             */
/*   Updated: 2023/10/28 14:09:54 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *stack)
{
	char	*buffer;
	int		read_byte;

	read_byte = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stack, '\n') && read_byte)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		stack = ft_strjoin(stack, buffer);
	}
	free(buffer);
	return (stack);
}

char	*gets_line(char *stack)
{
	char	*rtn;
	int		after_newline;
	int		i;

	i = 0;
	if (!stack || !stack[0])
		return (NULL);
	after_newline = newline_counter(stack);
	rtn = (char *)malloc(sizeof(char) * (after_newline + 2));
	if (!rtn)
		return (NULL);
	while (stack[i] && stack[i] != '\n')
	{
		rtn[i] = stack[i];
		i++;
	}
	if (stack[i] == '\n')
	{
		rtn[i] = '\n';
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*new_line(char *stack)
{
	char	*new_stack;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stack)
		return (NULL);
	while (stack[i] && stack[i] != '\n')
		i++;
	if (!stack[i])
	{
		free(stack);
		return (NULL);
	}
	new_stack = (char *)malloc(sizeof(char) * ((ft_strlen(stack) - i) + 1));
	if (!new_stack)
		return (NULL);
	i++;
	while (stack[i])
		new_stack[j++] = stack[i++];
	new_stack[j] = '\0';
	free(stack);
	return (new_stack);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stack = read_line(fd, stack);
	if (!stack)
		return (NULL);
	line = gets_line(stack);
	stack = new_line(stack);
	return (line);
}
