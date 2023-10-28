/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:57:08 by huates            #+#    #+#             */
/*   Updated: 2023/10/28 13:15:32 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *stack) // BUFFER_SIZE kadar okuyup stacke atıyor
{
	char	*buffer;
	int		read_byte;

	read_byte = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stack, '\n') && read_byte)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE); // read_byte = 0 ise dosya sonu demektir. -1 ise hata var demektir. BUFFER_SIZE kadar okuyor ve buffer'a atıyor.
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
        buffer[read_byte] = '\0';
        stack = ft_strjoin(stack, buffer);
	}
    free(buffer);
    return(stack);
}

char *get_line(char *stack) // stack içerisinde \n kadar okuyup line'a atıyor. Dizinin sonuna \n ve \0 ekliyor. 
{
	char *rtn;
	int after_newline; // \n sonrası için
	int i;
	
	i = 0;
	if (!stack || !stack[0])
		return (NULL);
	after_newline = newline_counter(stack); // \n öncesi karakter sayısı
	rtn = (char *)malloc(sizeof(char) * (after_newline + 2)); // \n ve \0 için 2 ekliyoruz
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

char *new_line(char *stack) // \n sonrası için yeni bir stack oluşturuyor. Çünkü \n sonrası yeni bir satır olabilir.
{
	char *new_stack;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!stack)
		return (NULL);
	while (stack[i] && stack[i] != '\n') // \n sonrası için i'yi \n'e getiriyoruz. Çünkü \n öncesi yeni satır. 
		i++;
	if (!stack[i]) // \n yoksa stack'i free edip NULL döndürüyor.
	{
		free(stack);
		return (NULL);
	}
	new_stack = (char *)malloc(sizeof(char) * ((ft_strlen(stack) - i) + 1)); // \n sonrası için yeni bir stack oluşturuyor. i kadar stack'i atlıyor. Çünkü i \n'e kadar okumuştu. Stack'den i çıkınca \n sonrası kalıyor.
	if (!new_stack)
		return (NULL);
	i++; // \n sonrası için i'yi 1 arttırıyor. Çünkü \n'yi atlamamız gerekiyor. Bize \n sonrası lazım.
	while (stack[i])
		new_stack[j++] = stack[i++];
	new_stack[j] = '\0';
	free(stack);
	return (new_stack);
}

char	*get_next_line(int fd)
{
	static char *stack; // static olduğu için her seferinde stack'i kaybetmiyoruz.
	char *line; // \n kadar okuyup line'a atıyoruz. Çünkü \n sonrası yeni satır bize tek satır lazım.

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stack = read_line(fd, stack); // BUFFER_SIZE kadar okuyup stack'e atıyor ancak \n içerisinde olabilir. Bunu kontrol etmemiz gerekiyor.
     if (!stack)
        return (NULL);
    line = get_line(stack); // Stack içerisinde \n kadar okuyup line'a atıyoruz. Dizinin sonuna \n ve \0 ekliyoruz. Çünkü \n sonrası yeni satır bize tek satır lazım.
	stack = new_line(stack); // \n sonrası için yeni bir stack oluşturuyor. Çünkü \n sonrası yeni bir satır.
	return (line);
}