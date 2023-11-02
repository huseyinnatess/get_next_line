/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:13:12 by huates            #+#    #+#             */
/*   Updated: 2023/11/02 14:13:19 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h> // read fonksiyonu için

static char	*ft_copy_to_stack(char *stack, char *buffer) // stack'e buffer'ı kopyalayan fonksiyon
{
	char	*new_stack; // yeni stack oluşturuyoruz

	new_stack = 0;
	if (!stack && buffer) // stack boşsa ve buffer doluysa çalışacak. Sadece ilk satır için çalışacak
	{
		new_stack = ft_strdup(buffer); // buffer'ı kopyalıyoruz
		if (!new_stack)
			return (NULL);
		return (new_stack);
	}
	new_stack = ft_strjoin(stack, buffer); // stack ve buffer'ı birleştiriyoruz
	ft_free_stack(&stack, 0); // stack'i free ediyoruz
	return (new_stack);
}

static int	newline_counter(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
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
	while (stack[i] != '\n') // stack'teki karakterleri '\n' olana kadar sayıyoruz
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2)); // '\n' karakteri ve '\0' karakteri için 2 ekliyoruz
	if (!line) 
		return (NULL);
	j = 0;
	while (j < (i + 1)) // '\n' karakterinide alması için i + 1 yapıyoruz
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
	while (stack[i] != '\n') // stack'teki karakterleri '\n' olana kadar sayıyoruz
		i++;
	if (stack[i + 1] == '\0') // '\n' karakterinden sonraki karakter '\0' ise NULL döndürüyoruz. Çünkü yeni satır yok.
		return (ft_free_stack(&stack, 0));
	new_stack = ft_substr(stack, i + 1, ft_strlen(stack)); // '\n' karakterinden sonraki karakterleri kopyalıyoruz
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
	char		buffer[BUFFER_SIZE + 1]; // buffer size + 1 kadar alan ayırıyoruz. NULL karakter dahil.
	long		read_byte; // read fonksiyonunun dönüş değeri için
	static char	*stack = NULL; 
	char		*line; // okunan satırı tutacak olan değişken

	line = 0;
	read_byte = BUFFER_SIZE; // While döngüsüne girebilmek için read_byte değerini BUFFER_SIZE'a eşitliyoruz.(0 harici istediğniz değeri verebilirsiniz)
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack, 0));
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE); // read fonksiyonu ile buffer'a okuma yapıyoruz.
		if ((read_byte <= 0 && !stack) || read_byte == -1)
			return (ft_free_stack(&stack, 0));
		buffer[read_byte] = '\0'; // buffer'ın sonuna NULL karakteri ekliyoruz.
		stack = ft_copy_to_stack(stack, buffer);
		if (newline_counter(stack)) // sadece stack içinde \n varsa çalışacak
		{
			line = gets_line(stack); // stack içindeki satırı line'a kopyalıyoruz. \n'den önceki kısmı kopyalıyor. Çünkü \n sonrası yeni satırın karakterleri
			if (!line)
				return (ft_free_stack(&stack, 0));
			return (stack = new_line(stack), line); 
		}
	}
	return (ft_free_stack(&stack, 1));
}

// Readme daha açıklayıcılı bir şekilde bilgiler var.
