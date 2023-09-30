#include "get_next_line.h"

char *read_line(int fd, char *stack)
{
    char *buffer;
    int read_byte;

    read_byte = 1;
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    while (!ft_strchr(stack, '\n') && read_byte)
    {
        read_byte = read(fd, buffer, BUFFER_SIZE); // Main'de open ile açtığımız dosyaya burada erişim sağlıyoruz. Dosyadaki veriler buffer size miktarı kadar okunup buffer'a kaydedilir.
        if (read_byte == -1)                        // Sadece tek satır okumuyor. Buffersize göre karakter karakter okuyup (buffersize 2 ise dosyadaki verileri 2'şer byte okur. Örn. veri Merhaba fonksiyon Me, rh, ab şeklinde) join ile stacke kaydeder.                                                   
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

char *new_line(char *str)
{
    int i;
    int j;
    char *rest;

    i = 0;
    j = 0;
    if (!str)
        return (NULL);
    while (str[i] != '\n' && str[i])
        i++;
    if (!str[i])
    {
        free(str);
        return (NULL);
    }
    rest = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1)); // '\n' önesindeki kısımlar hesaplanmıyor. Yeni satır lazım bize.
    if (!rest)
        return (NULL);
    i++;
    while (str[i])
        rest[j++] = str[i++];
    rest[j] = '\0';
    free(str);
    return (rest);

    // İlk satır haricinde kalan verileri rest'e kaydeder.
} 

char *get_line(char *stack)
{
    char *ret;
    int after_newline;
    int i;

    i = 0;
    if (!stack || stack[0] == '\0')
        return (NULL);
    after_newline = newline_counter(stack);
    ret = (char *)malloc(sizeof(char) * (after_newline + 2));// 2 eklenmesinin sebebi NULL ve '\n' içinde yer ayrımak.
    if (!ret)
        return (NULL);
    while (stack[i] && stack[i] != '\n')
    {
        ret[i] = stack[i];
        i++;
    }
    if (stack[i] == '\n')
    {
        ret[i] = stack[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
    // İlk satırı return ediyor.
}

char *get_next_line(int fd)
{
    static char *stack;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stack = read_line(fd, stack);
    if (!stack)
        return (NULL);
    line = get_line(stack);
    stack = new_line(stack);
    return (line);
}