/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:56:47 by huates            #+#    #+#             */
/*   Updated: 2023/10/28 13:08:28 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
 
# include <fcntl.h>
# include <stdio.h> //main için yazıldı geri sil.
# include <stdlib.h>
# include <unistd.h>

int	    ft_strlen(const char *str);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_strchr(char *s, int c);
char	*get_next_line(int fd);
char	*get_line(char *stack);
char	*new_line(char *str);
char	*read_line(int fd, char *stack);
int     newline_counter(char *str);

#endif