/*
** message.c for  in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/server_src
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun Jun  5 08:33:00 2016 Sebastien Fourtou
** Last update Sun Jun  5 09:02:31 2016 Sebastien Fourtou
*/

#include "server.h"

#define print_and_leave(x, y)  {\
    dprintf(x, y);\
    return;\
  }\

int is_connected_to(char * recipient, t_channel * channels)
{
  while (channels)
    {
      if (strcmp(recipient, channels->name) == 0)
	return (0);
      channels = channels->next;
    }
  return (1);
}

void send_to_channel(char * recipient, t_env * env, char * message)
{
  t_channel * channels;
  t_env * first;

  first = env->first;
  while (first)
    {
      if (first->fd_type == FD_CLIENT)
	{
	  channels = first->channels;
	  while (channels)
	    {
	      if (strcmp(recipient, channels->name) == 0 && first->fd != env->fd)
		dprintf(first->fd, ":%s!127.0.0.1 PRIVMSG %s :%s\r\n",
			env->nickname, recipient, message);
	      channels = channels->next;
	    }
	}
      first = first->next;
    }
}

void send_to_nickname(char * recipient, t_env * env, char * message)
{
  t_env * first;

  first = env->first;
  while (first)
    {
      if (first->fd_type == FD_CLIENT)
	{
	  if (strcmp(recipient, first->nickname) == 0)
	    dprintf(first->fd, ":%s!127.0.0.1 PRIVMSG %s :%s\r\n",
		    env->nickname, recipient, message);
	}
      first = first->next;
    }
}

void send_private_message(t_env **env)
{
  char * recipient;
  char * message;

  strtok((*env)->last_message, " ");
  recipient = strtok(NULL, " ");
  message = strtok(NULL, " ");
  if (recipient == NULL)
    print_and_leave((*env)->fd, "411 :No recipient given\r\n")
  if (message == NULL)
    print_and_leave((*env)->fd, "412 :No text to send\r\n")
  if (is_channel(recipient) == 0)
    {
      if (is_connected_to(recipient, (*env)->channels) == 0)
	send_to_channel(recipient, *env, message);
      else
	{
	  dprintf((*env)->fd, "404 %s :Cannot send to channel\r\n", recipient);
	  return;
	}
    }
  else if (is_nickname(recipient, (*env)->first) == 0)
    send_to_nickname(recipient, *env, message);
  else
    dprintf((*env)->fd, "401 %s :No such nick/channel\r\n", recipient);
}
