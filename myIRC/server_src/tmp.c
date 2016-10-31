/*
** tmp.c for  in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/server_src
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun Jun  5 08:52:45 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:53:18 2016 Sebastien Fourtou
*/

#include "server.h"

void print_on_quit_channel(char * channel_name, char * nickname, t_env * env)
{
  t_channel * channel;

  while (env)
    {
      if (env->fd_type == FD_CLIENT)
	{
	  channel = env->channels;
	  while (channel)
	    {
	      if (strcmp(channel_name, channel->name) == 0)
		dprintf(env->fd, ":%s!127.0.0.1 PART %s\r\n", nickname, channel_name);
	      channel = channel->next;
	    }
	}
      env = env->next;
    }
}

void print_on_channel(char * channel_name, char * nickname, t_env * env)
{
  t_channel * channel;

  while (env)
    {
      if (env->fd_type == FD_CLIENT)
	{
	  channel = env->channels;
	  while (channel)
	    {
	      if (strcmp(channel_name, channel->name) == 0)
		dprintf(env->fd, ":%s!127.0.0.1 JOIN %s\r\n", nickname, channel_name);
	      channel = channel->next;
	    }
	}
      env = env->next;
    }
}

void quit_channel(t_env ** env)
{
  char * param;
  int ret;

  strtok((*env)->last_message, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      asprintf(&(*env)->reply, "/PART: Not enough parameter\n");
      return;
    }
  ret = pop_channel(param, &(*env)->channels);
  if (ret == 1)
    {
      asprintf(&(*env)->reply, "403 %s: No such channel\n", param);
      return;
    }
  else if (ret == 2)
    {
      asprintf(&(*env)->reply, "442 %s: You're not\
connected on that channel\n", param);
      return;
    }
  print_on_quit_channel(param, (*env)->nickname, (*env)->first);
  dprintf((*env)->fd, ":%s!127.0.0.1 PART %s\r\n", (*env)->nickname, param);
}
