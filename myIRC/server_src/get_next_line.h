/*
** get_next_line.h for get in /home/nicolasmarchal/rendu/getnextline/test1/CPE_2014_get_next_line
** 
** Made by nicolas marchal
** Login   <marcha_0@epitech.net>
** 
** Started on  Fri Nov 21 23:38:00 2014 nicolas marchal
** Last update Mon Jan 19 13:12:22 2015 nicolas marchal
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define SIZE 4096

void	buf_init(char *str, int taille);
char	*my_realloc(char *str, int taille);
int	still_tmp(char *tmp, char *buf, int i, int ret);
char	*read_line(const int fd, char *str, char *tmp, int j);
char    *get_next_line(const int fd);

# endif /* !GET_NEXT_LINE_H_ */
