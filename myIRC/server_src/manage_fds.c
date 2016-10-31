/*
** manage_fds.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 22 11:48:18 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:53:39 2016 Sebastien Fourtou
*/

#include "server.h"

void init_set_fd(t_env * env, fd_set * set_read, fd_set * set_write)
{
  FD_ZERO(set_read);
  FD_ZERO(set_write);
  while (env)
    {
      if (env->fd_type != FD_FREE)
	{
	  FD_SET(env->fd, set_read);
	  if (env->fd_type == FD_CLIENT)
	    FD_SET(env->fd, set_write);
	}
      env = env->next;
    }
}

int get_max_fd(t_env * env)
{
  int max;

  if (env->fd_type != FD_FREE)
    max = env->fd;
  while (env)
    {
      if (env->fd_type != FD_FREE && max < env->fd)
	max = env->fd;
      env = env->next;
    }
  return (max);
}

void check_changes_fd(t_env ** env, fd_set * set_read, fd_set * set_write)
{
  t_env * tmp;

  tmp = *env;
  while (tmp)
    {
      tmp->first = *env;
      if (FD_ISSET(tmp->fd, set_read))
	(*tmp->fct_read)(&tmp);
      if (FD_ISSET(tmp->fd, set_write))
	(*tmp->fct_write)(&tmp);
      tmp = tmp->next;
    }
}
