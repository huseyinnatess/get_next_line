/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huates <huates@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:03:47 by huates            #+#    #+#             */
/*   Updated: 2023/10/28 13:08:33 by huates           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strchr(char *s, int c)
{
    int i;

    i = -1;
    if (!s)
        return (0);
    if (c == '\0')
        return ((char *)&s[ft_strlen(s)]); // Eğer aranan karakter NULL ise s dizisinin son karakterinin (NULL) adresini char * olarak return ediyor.
    while (s[++i])
    {
        if (s[i] == (char)c)
            return ((char *)&s[i]);
    }
    return (0);
}

char *ft_strjoin(char *str1, char *str2)
{
    size_t i;
    size_t j;
    char *str;

    i = -1;
    j = 0;
    if (!str1)
    {
        str1 = (char *)malloc(sizeof(char) * 1); // str1 NULL ise 1 byte yer ayırıyor ve ilk byte'ı NULL yapıyor.
        str1[0] = '\0';
    }
    if (!str1 || !str2)
        return (NULL);
    str = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1);
    if (!str)
        return (NULL);
    while (str1[++i])
        str[i] = str1[i];
    while (str2[j])
        str[i++] = str2[j++];
    str[ft_strlen(str1) + ft_strlen(str2)] = '\0';
    free(str1);
    return (str);
}

int newline_counter(char *str)
{
    int counter;
    
    counter = 0;
    while (str[counter] != '\n' && str[counter])
        counter++;
    return (counter);
}