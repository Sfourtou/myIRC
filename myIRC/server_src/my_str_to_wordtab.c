/*
** my_str_to_wordtab.c for  in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/server_src
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun Jun  5 08:25:31 2016 Sebastien Fourtou
** Last update Sun Jun  5 09:00:53 2016 Sebastien Fourtou
*/

#include <stdlib.h>
#include "server.h"

void launch_list_on_all_next(t_env * tmp, t_channel * tmp1,
			     t_channel * tmp2, int fd_reply)
{
  while (tmp2)
    {
      if (tmp2->id_channel == tmp1->id_channel)
	dprintf(fd_reply, "%s ", tmp->nickname);
      tmp2 = tmp2->next;
    }
}

void launch_list_on_all(t_env * env, char ** reply, int fd_reply)
{
  t_env * tmp;
  t_channel * tmp1;
  t_channel * tmp2;

  tmp1 = ch;
  (*reply == NULL) ? *reply = "" : 0;
  while (tmp1)
    {
      dprintf(fd_reply, "353 %s: ", tmp1->name);
      tmp = env;
      while (tmp)
	{
	  if (tmp->fd_type == FD_CLIENT)
	    {
	      tmp2 = tmp->channels;
	      launch_list_on_all_next(tmp, tmp1, tmp2, fd_reply);
	    }
	  tmp = tmp->next;
	}
      dprintf(fd_reply, "\r\n");
      tmp1 = tmp1->next;
    }
  dprintf(fd_reply, "353 End of /NAMES list.\r\n");
}

int count_word(char * str, char delim)
{
  int i;
  int count;

  i = -1;
  count = 0;
  while (str[++i] && str[i] != delim)
    {
      ++count;
    }
  return (count + 1);
}

int len_word(char *str, char delim, int i)
{
  int count;

  count = 0;
  while (str[i] && str[i] != delim)
    {
      ++count;
      ++i;
    }
  return (count);
}

char ** my_str_to_wordtab(char * str, char delim)
{
  char ** tab;
  int i;
  int j;
  int k;

  i = 0;
  if ((tab = malloc(sizeof(char *) * count_word(str, delim))) == NULL)
    return (NULL);
  k = 0;
  while (str[i])
    {
      if ((tab[k] = malloc(sizeof(char) * (len_word(str, delim, i) + 1))) == NULL)
	return (NULL);
      j = -1;
      while (str[i] && str[i] != delim)
	tab[k][++j] = str[i++];
      tab[k][++j] = 0;
      if (str[i])
	++i;
      ++k;
    }
  tab[k] = NULL;
  return (tab);
}
