/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:08:45 by kkanyilm          #+#    #+#             */
/*   Updated: 2023/11/01 17:01:04 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
	
static char	*ft_copy_to_stack(char *stack, char *buffer)
{
	char	*new_stack;

	new_stack = 0;
	if (!stack && buffer)
	{
		new_stack = ft_strdup(buffer);
		if (!new_stack)
			return (NULL);
		return (new_stack);
	}
	new_stack = ft_strjoin(stack, buffer);
	ft_free_stack(&stack, 0);
	return (new_stack);
}

static int	newline_counter(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			return (1);
	return (0);
}

static char	*gets_line(char *stack)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stack)
		return (0);
	while (stack[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < (i + 1))
	{
		line[j] = stack[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*new_line(char *stack)
{
	size_t	i;
	char	*new_stack;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	if (stack[i + 1] == '\0')
		return (ft_free_stack(&stack, 0));
	new_stack = ft_substr(stack, i + 1, ft_strlen(stack));
	if (!new_stack)
	{
		ft_free_stack(&stack, 0);
		return (NULL);
	}
	ft_free_stack(&stack, 0);
	return (new_stack);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		read_byte;
	static char	*stack = NULL;
	char		*line;

	line = 0;

	printf("%d", BUFFER_SIZE);
	return (0);
	read_byte = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack, 0));
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if ((read_byte <= 0 && !stack) || read_byte == -1)
			return (ft_free_stack(&stack, 0));
		buffer[read_byte] = '\0';
		stack = ft_copy_to_stack(stack, buffer);
		if (newline_counter(stack))
		{
			line = gets_line(stack);
			if (!line)
				return (ft_free_stack(&stack, 0));
			return (stack = new_line(stack), line);
	
		}
	}
	return (ft_free_stack(&stack, 1));
}
