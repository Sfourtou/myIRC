/*
** manage_client.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 22 11:46:33 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:46:44 2016 Sebastien Fourtou
*/

#include "get_next_line.h"
#include "server.h"

void read_client(t_env **env)
{
  int r;
  char buffer[4096];
  char ** tab;
  int i;

  if ((r = read((*env)->fd, buffer, 4096)) > 0)
    {
      (r > 1) ? buffer[r] = 0 : 0;
      tab = my_str_to_wordtab(buffer, '\n');
      i = -1;
      while (tab[++i])
      	{
      	  if (tab[i][strlen(tab[i]) - 1] == '\r')
      	    tab[i][strlen(tab[i]) - 1] = '\0';
	  (*env)->last_message = strdup(tab[i]);
	  do_command(env);
	  free((*env)->last_message);
	}
    }
  else
    {
      printf("%d : Connection closed\n", (*env)->fd);
      close((*env)->fd);
      (*env)->fd_type = FD_FREE;
    }
}

void write_client(t_env ** env)
{
  t_env * tmp;

  return;
  tmp = *env;
  while (tmp)
    {
      if (tmp->fd_type == FD_CLIENT && tmp->reply != NULL)
	{
	  dprintf(tmp->fd, "%s", tmp->reply);
	  free(tmp->reply);
	  tmp->reply = NULL;
	}
      tmp = tmp->next;
    }
  return;
}

void get_reply(int fd)
{
  dprintf(fd, "001 Hello\r\n002 Bonjour\r\n003 Comment ca va\r\n004 Ca va\r\n");
}

void add_client(t_env ** env)
{
  t_env * new;
  t_env * tmp;
  struct sockaddr_in sin;
  socklen_t len_sin;

  len_sin = sizeof(sin);
  tmp = *env;
  if ((new = malloc(sizeof(*new))) == NULL)
    perror("Malloc");
  if ((new->fd = accept(tmp->fd, (struct sockaddr *)&sin, &len_sin)) == -1)
    exit(EXIT_SUCCESS);
  new->fd_type = FD_CLIENT;
  new->fct_read = read_client;
  new->fct_write = write_client;
  new->fct = init_command();
  new->reply = NULL;
  get_reply(new->fd);
  new->channels = NULL;
  asprintf(&new->nickname, "Anonymous%d", new->fd);
  new->next = NULL;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
}
