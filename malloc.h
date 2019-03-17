#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define UNUSED 0
# define USED   1

typedef struct  s_list
{
  size_t    size;
  int       is_used;
  void      *addr;
  int       head;
  struct s_list *prev;
  struct s_list *next;
}       t_list;

void    *malloc(size_t size);
void    put_in_list(t_list **list, size_t size, void *addr);
void    free(void *ptr);
void    make_circle(t_list **list);
void    show_alloc_mem();
void    *realloc(void *ptr, size_t size);
size_t  get_size(void *ptr);
void    re_init_list();
void    *find_block(size_t size);
int is_in_list(void *ptr);

#endif /* !MALLOC_H_ */
