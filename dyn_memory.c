#include "malloc.h"

t_list      *g_list;

void        *malloc(size_t size)
{
  void      *addr;
  static int    i = 0;

  if (size == 0)
    return (NULL);
  size = (size - 1) / 4 * 4 + 4;
  addr = find_block(size);
  if (addr != NULL)
    {
      re_init_list();
      return (addr);
    }
  addr = sbrk(size);
  if (addr == (void *)-1)
    {
      printf("Error : sbrk() failed\n");
      return (NULL);
    }
  if (i == 0)
    g_list = NULL;
  put_in_list(&g_list, size, addr);
  ++i;
  return (addr);
}


void        *find_block(size_t size)
{
  if (g_list == NULL)
    return (NULL);
  if (g_list->is_used == UNUSED && size <= g_list->size)
    {
      g_list->is_used = USED;
      return (g_list->addr);
    }
  while(g_list->head != 1)
    {
      if (g_list->is_used == UNUSED && size <= g_list->size)
    {
      g_list->is_used = USED;
      return (g_list->addr);
    }
      g_list = g_list->next;
    }
  re_init_list();
  return (NULL);
}


void        put_in_list(t_list **list, size_t size, void *addr)
{
  t_list    *tmp;

  tmp = sbrk(sizeof(*tmp));
  if (tmp == (void *)-1)
    {
      printf("Error : sbrk() failed\n");
      return ;
    }
  tmp->size = size;
  tmp->is_used = USED;
  tmp->addr = addr;
  if (*list == NULL)
    tmp->head = 1;
  else
    {
      tmp->head = 0;
      tmp->next = *list;
      if (tmp->next)
    tmp->next->prev = tmp;
    }
  *list = tmp;
  make_circle(list);
}
void        make_circle(t_list **list)
{
  t_list    *tmp;

  tmp = *list;
  while ((*list)->head != 1)
    (*list) = (*list)->next;
  (*list)->next = tmp;
  (*list)->next->prev = *list;
  while ((*list) != tmp)
    *list = (*list)->next;
}

void    re_init_list()
{
  while (g_list->head != 1)
    g_list = g_list->next;
  g_list = g_list->next;
}

void    free(void *ptr)
{
  if (ptr == NULL)
    return ;
  if (is_in_list(ptr) == 1)
    return ;
  while (ptr != g_list->addr && g_list->head != 1)
    g_list = g_list->next;
  if (g_list->is_used == UNUSED)
    return ;
  g_list->is_used = UNUSED;
  if (g_list->head != 1)
    {
      if (g_list->next->is_used == UNUSED &&
      g_list->next->addr != g_list->addr)
    {
      if (g_list->addr > g_list->next->addr)
        g_list->addr = g_list->next->addr;
      g_list->head = g_list->next->head;
      g_list->size += g_list->next->size;
      g_list->next = g_list->next->next;
    }
    }
  re_init_list();
}


void        *realloc(void *ptr, size_t size)
{
  void      *cpy;
  size_t    ptr_size;

  if (size == 0 && ptr != NULL)
    {
      free(ptr);
      return (ptr);
    }
  else if (ptr == NULL || is_in_list(ptr) == 1)
    ptr = malloc(size);
  else
    {
      ptr_size = get_size(ptr);
      if (ptr_size == size)
        return (ptr);
      cpy = malloc(size);
      if (size < ptr_size)
        memcpy(cpy, ptr, size);
      else
        memcpy(cpy, ptr, ptr_size);
      free(ptr);
      return (cpy);
    }
  return (ptr);
}
int is_in_list(void *ptr)
{
  t_list    *tmp;

  tmp = g_list;
  while (tmp->addr != ptr && tmp->head != 1)
    tmp = tmp->next;
  if (tmp->addr != ptr)
    return (1);
  return (0);
}

size_t      get_size(void *ptr)
{
  t_list    *tmp;

  tmp = g_list;
  while (tmp->addr != ptr)
    tmp = tmp->next;
  return (tmp->size);
}
