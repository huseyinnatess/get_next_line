#include "get_next_line.h"

int main()
{
    int fd; // Dosya tanımlayıcısı değişkeni. Ataması sistem tarafından yapılır. Sistemdeki dosyaya erişmek için kullanılır.
    char *line;
    fd = open("test.txt", O_RDONLY); // Sistem tarafından otomatik olarak genellikle 3 sayısı return edilir.
    line = get_next_line(fd); // Okunacak satır.

    printf("%s", line);
    free(line);
   
    return (0);
}

/*
O_RDONLY Sadece okumak için
O_WRONLY Sadece yazmak için
O_RDWR Hem yazmak hem okumak için
O_CREAT Dosya yoksa dosyayı oluştur
O_NOFOLLOW Sembolik linkleri takip etme
O_APPEND Dosyaya yazmaları dosyanın sonuna yap
O_ASYNC Dosyaya girdi/Çıktı mümkünse signal yay
O_TRUNC Dosyanın sonunu keser

*/

/*

int main()
{
  // Bir dosya tanımlayıcısı değişkeni tanımlıyoruz.
  int fd;

  // Bir dosya açıyoruz ve bu fonksiyon bize tanımlayıcı dönüyor.
  // Genellikle 3 döner.
  fd = open("my_file.txt", O_RDONLY);
  
  // Açılan dosyaya erişim sağlıyoruz.
  char buffer[100];
  read(fd, buffer, 100);

  // Okuduğumuz veriyi ekrana bastırabiliriz.
  printf("%s", buffer);

  // Dosyamızı kapatıyoruz.
  close(fd);
  
  return (0);
}

*/