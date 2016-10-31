/*
** manage_sockets.c for  in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/client_src
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun Jun  5 08:22:36 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:43:56 2016 Sebastien Fourtou
*/

#include "client.h"

void init_my_sockets(fd_set * set_read, fd_set * set_write, int fd)
{
  FD_ZERO(set_read);
  FD_ZERO(set_write);
  FD_SET(0, set_read);
  FD_SET(1, set_write);
  FD_SET(fd, set_read);
  FD_SET(fd, set_write);
}
