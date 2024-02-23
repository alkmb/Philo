#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *ft_strncpy(char *s1, char *s2, int n)
{
  int i = 0;

  while (i < n)
  {
    s1[i] = s2[i];
    i++;
  }
  s1[i] = '\0';
  return s1;
}

char  **ft_split(char *str)
{
  int i = 0;
  int j = 0;
  int k = 0;
  char **out;

  out = (char **)malloc(1000 * sizeof(char *));
  while (str[i])
  {
    while (str[i] && str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
      i++;
    j = i;
    while (str[i] && str[i] != ' ' || (str[i] <= 9 && str[i] >= 13))
      i++;
    if (i > j)
    {
      out[k] = (char *)malloc(1000 * sizeof(char));
      ft_strncpy(out[k++], &str[j], i - j);
    }
  }
  out[k] = '\0';
  return (out);
}

int main(int argc, char **argv)
{
  if (argc != 2)
    write (1, "\n", 1);
  else 
  {
    int i = 0;
    char **str;

    str = ft_split(argv[1]);
    while (str[i])
      printf("%s\n", str[i++]);
  }
}
