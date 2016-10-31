/*
** get_next_line.c for  in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myftp
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 15 06:07:47 2016 Sebastien Fourtou
** Last update Sun May 15 06:07:49 2016 Sebastien Fourtou
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

void	buf_init(char *str, int	size)
{
  int	i;

  i = -1;
  while (++i < size)
    str[i] = 0;
}

char	*my_realloc(char *str, int size)
{
  char	*new_str;
  int	i;
  int	len;

  len = -1;
  while (str[++len]);
  i = -1;
  if ((new_str = malloc(sizeof(char) * (len + size + 1))) == NULL)
    return (NULL);
  buf_init(new_str, (len + size + 1));
  while (str[++i])
    new_str[i] = str[i];
  free(str);
  return (new_str);
}

int	still_tmp(char *tmp, char *buf, int i, int ret)
{
  int	j;

  j = -1;
  if (buf[i] == '\n' || ret < SIZE)
    {
      while (buf[i])
	tmp[++j] = buf[++i];
      return (1);
    }
  return (0);
}

char	*read_line(const int fd, char *str, char *tmp, int j)
{
  int	i;
  int	ret;
  char	buf[SIZE + 1];
  int	countread;

  countread = 0;
  buf_init(buf, SIZE + 1);
  while ((ret = read(fd, buf, SIZE)) > 0)
    {
      if ((str = my_realloc(str, ret)) == NULL)
	return (NULL);
      i = 0;
      while (buf[i] != '\n' && i < ret)
	str[j++] = buf[i++];
      if ((still_tmp(tmp, buf, i, ret)) == 1)
	return (str);
      buf_init(buf, SIZE + 1);
      countread = 1;
    }
  if (countread == 1 || j > 0)
    return (str);
  free(str);
  return (NULL);
}

char		*get_next_line(const int fd)
{
  static char	tmp[SIZE + 1];
  static int	i = 0;
  char		*str;
  int		j;

  j = 0;
  if ((str = malloc(sizeof(char) * SIZE + 1)) == NULL)
    return (NULL);
  buf_init(str, SIZE + 1);
  while (tmp[i] && tmp[i] != '\n')
    str[j++] = tmp[i++];
  if (tmp[i] != '\n')
    {
      i = 0;
      buf_init(tmp, SIZE + 1);
      if ((str = read_line(fd, str, tmp, j)) == NULL)
	return (NULL);
    }
  else
    i++;
  return (str);
}
