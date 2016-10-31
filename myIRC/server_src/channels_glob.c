/*
** channels.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 22 20:16:04 2016 Sebastien Fourtou
** Last update Tue May 24 14:52:19 2016 Sebastien Fourtou
*/

#include "server.h"

int is_known_channel(char * channel_name)
{
  t_channel * tmp;

  tmp = ch;
  while (tmp)
    {
      printf("%s\n", channel_name);
      if (strcmp(channel_name, tmp->name) == 0)
	return (0);
      tmp = tmp->next;
    }
  return (1);
}

void create_new_channel(char * channel_name)
{
  int i;
  t_channel * new;
  t_channel * tmp;

  if ((new = malloc(sizeof(*new))) == NULL)
    return;
  new->name = strdup(channel_name);
  new->next = NULL;
  if (ch == NULL)
    {
      new->id_channel = 0;
      ch = new;
      return;
    }
  tmp = ch;
  i = 1;
  while (tmp->next != NULL)
    {
      tmp = tmp->next;
      ++i;
    }
  new->id_channel = i;
  tmp->next = new;
}

void list_channels(t_env ** env)
{
  t_channel * tmp;

  if ((*env)->reply == NULL)
    (*env)->reply = "";
  tmp = ch;
  while (tmp)
    {
      (*env)->reply = my_strcat((*env)->reply, "322 ");
      (*env)->reply = my_strcat((*env)->reply, tmp->name);
      (*env)->reply = my_strcat((*env)->reply, "\n");
      tmp = tmp->next;
    }
  (*env)->reply = my_strcat((*env)->reply, "323 End of /LIST list.\n");
}
