#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strjoin(char *left_str, char *buff)
{
    size_t i;
    size_t j;
    char *str;

    if (!left_str)
    {
        left_str = (char *)malloc(sizeof(char) * 1);
        left_str[0] = '\0';
    }
    if (!left_str || !buff)
        return (NULL);
    str = (char *)malloc(sizeof(char) * ft_strlen(left_str) + ft_strlen(buff) + 1);
    if (!str)
        return (NULL);
         
    i = -1;
    j = 0;
    if (left_str)
        while(left_str[++i])
            str[i] = left_str[i];
    while (buff[j])
        str[i++] = buff[j++];
    str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
    free(left_str);
    return (str);
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

int newline_counter(char *str)
{
    int counter;
    
    counter = 0;
    while (str[counter] != '\n' && str[counter])
        counter++;
    return (counter);
}