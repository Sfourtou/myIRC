/*
** my_channels.c for PSU_2015_myirc in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Tue May 24 14:49:15 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:55:05 2016 Sebastien Fourtou
*/

#include "server.h"

static void push_channels(t_channel ** channels, t_channel * channel)
{
  t_channel * new;
  t_channel * tmp;

  if ((new = malloc(sizeof(*new))) == NULL)
    return;
  new->id_channel = channel->id_channel;
  new->name = channel->name;
  new->next = NULL;
  if (*channels == NULL)
    {
      *channels = new;
      return;
    }
  tmp = *channels;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
}

static void connect_to_channel(t_env ** env, char * channel_name)
{
  t_channel * tmp;

  tmp = ch;
  while (tmp)
    {
      if (strcmp(channel_name, tmp->name) == 0)
	{
	  push_channels(&(*env)->channels, tmp);
	  return;
	}
      tmp = tmp->next;
    }
}

int channel_exist(t_channel * tmp, char * channel_name)
{
  int find;

  find = 0;
  while (tmp)
    {
      (strcmp(tmp->name, channel_name) == 0) ? find = 1 : 0;
      tmp = tmp->next;
    }
  if (find == 0)
    return (1);
  return (0);
}

int pop_channel(char * channel_name, t_channel ** chanel)
{
  t_channel * tmp;
  t_channel * to_free;

  tmp = ch;
  if (channel_exist(tmp, channel_name) == 1)
    return (1);
  tmp = *chanel;
  if (tmp->next == NULL && strcmp(tmp->name, channel_name) == 0)
    {
      free(*chanel);
      *chanel = NULL;
      return (0);
    }
  while (tmp->next)
    {
      if (tmp->next != NULL && strcmp(tmp->next->name, channel_name) == 0)
	{
	  to_free = tmp->next;
	  tmp->next = tmp->next->next;
	  free(to_free);
	  return (0);
	}
      tmp = tmp->next;
    }
  return (2);
}

void manage_join(t_env ** env)
{
  char * channel_name;

  strtok((*env)->last_message, " ");
  channel_name = strtok(NULL, " ");
  if (channel_name == NULL)
    {
      dprintf((*env)->fd, "461 JOIN: Not enough parameter\r\n");
      return;
    }
  if (is_known_channel(channel_name) == 0)
    connect_to_channel(env, channel_name);
  else
    {
      create_new_channel(channel_name);
      connect_to_channel(env, channel_name);
    }
  print_on_channel(channel_name, (*env)->nickname, (*env)->first);
  launch_list_for_param(channel_name, (*env)->first, &(*env)->reply, (*env)->fd);
}
