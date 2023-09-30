# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

#include <stdio.h> //main için yazıldı geri sil.

int		ft_strlen(char *str);
int		newline_counter(char *str);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_strchr(char *str, int c);
char	*get_next_line(int fd);
char	*get_line(char *stack);
char	*new_line(char *str);
char	*read_line(int fd, char *stack);

# endif
