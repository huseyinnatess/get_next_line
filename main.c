/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:50:19 by huates            #+#    #+#             */
/*   Updated: 2023/10/28 14:04:26 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*stack;
	int		i;

	i = 1;
	fd = open("test.txt", O_RDONLY);
	stack = get_next_line(fd);
	while (fd && stack)
	{
		printf("%d. Satir: %s\n", i++, stack);
		stack = get_next_line(fd);
	}
	close(fd);
	return (0);
}
