/*
** miscelleanous.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 22 13:58:38 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:32:04 2016 Sebastien Fourtou
*/

#include "server.h"

void list_users(t_env ** env)
{
  t_env * first;

  first = (*env)->first;
  if (((*env)->reply = malloc(sizeof(char) * (10))) == NULL)
   return;
  while (first)
    {
      if (first->nickname != NULL)
	dprintf((*env)->fd, "393 %s\r\n", first->nickname);
      first = first->next;
    }
  dprintf((*env)->fd, "394 End of /USERS list\r\n");
}

void launch_list_for_param(char * name, t_env * env, char ** reply, int fd_reply)
{
  t_env * tmp;
  t_channel * tmp1;

  tmp = env;
  if (*reply == NULL)
    *reply = "";
  dprintf(fd_reply, "353 %s : ", name);
  while (tmp)
    {
      if (tmp->fd_type == FD_CLIENT)
	{
	  tmp1 = tmp->channels;
	  while (tmp1)
	    {
	      if (tmp1->name != NULL && strcmp(tmp1->name, name) == 0)
		dprintf(fd_reply, "%s ", tmp->nickname);
	      tmp1 = tmp1->next;
	    }
	}
      tmp = tmp->next;
    }
  dprintf(fd_reply, "\r\n");
  dprintf(fd_reply, "366 %s :End of /NAMES list\r\n", name);
}

void list_users_channel(t_env ** env)
{
  char * param;

  strtok((*env)->last_message, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      launch_list_on_all((*env)->first, &(*env)->reply, (*env)->fd);
      return;
    }
  launch_list_for_param(param, (*env)->first, &(*env)->reply, (*env)->fd);
}

int is_use(char * nickname, t_env * env, int fd)
{
  while (env)
    {
      if (env->nickname != NULL && fd != env->fd)
	{
	  if (strcmp(nickname, env->nickname) == 0)
	    return (0);
	}
      env = env->next;
    }
  return (1);
}

void change_nickname(t_env ** env)
{
  char * param;

  strtok((*env)->last_message, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      dprintf((*env)->fd, "431 No nickname given\r\n");
      return;
    }
  if (strlen(param) > 9)
    {
      dprintf((*env)->fd, "432 %s: Erroneus nickname\r\n", param);
      return;
    }
  if (is_use(param, (*env)->first, (*env)->fd) == 0)
    {
      dprintf((*env)->fd, "433 %s: Nickname already in used\r\n", param);
      return;
    }
  if ((*env)->nickname != NULL)
    dprintf((*env)->fd, ":%s!127.0.0.1 NICK %s\r\n", (*env)->nickname, param);
  (*env)->nickname = strdup(param);
}
