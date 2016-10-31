/*
** verif.c for  in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun Jun  5 09:01:31 2016 Sebastien Fourtou
** Last update Sun Jun  5 09:01:42 2016 Sebastien Fourtou
*/

#include "server.h"

int is_channel(char * recipient)
{
  t_channel * tmp;

  tmp = ch;
  while (tmp)
    {
      if (strcmp(recipient, tmp->name) == 0)
	return (0);
      tmp = tmp->next;
    }
  return (1);
}

int is_nickname(char * recipient, t_env * env)
{
  while (env)
    {
      if (env->fd_type == FD_CLIENT)
	{
	  if (strcmp(recipient, env->nickname) == 0)
	    return (0);
	}
      env = env->next;
    }
  return (1);
}
