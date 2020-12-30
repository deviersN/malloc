/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** header
*/

#ifndef MALLOC_H_
# define MALLOC_H_

#include <pthread.h>
#include <stddef.h>

typedef struct		s_data
{
	size_t		size;
	struct s_data	*next;
	struct s_data	*prev;
	int		available;
	void		*ptr;
	char		end[1];
}			t_data;

#define BLOCK_SIZE 40

pthread_mutex_t		mutex;

/* malloc.c */
void			*malloc(size_t size);

/* malloc_extension.c */
t_data			*extend_or_not(const size_t size);

/* free.c */
void			free(void *ptr);

/* realloc.c */
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t nmenb, size_t size);

/* show_alloc_mem.c */
void			show_alloc_mem(void);

/* shared_function.c */
size_t			align_size(size_t x);
size_t			get_and_set_size_break(const size_t size, const int);
t_data			*get_and_set_list(const int get_set, t_data *data);
t_data			*get_valid_node(void *data);

#endif /* !MALLOC_H_ */