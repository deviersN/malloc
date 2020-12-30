/*
** EPITECH PROJECT, 2018
** Malloc
** File description:
** 
*/

#include <pthread.h>
#include <unistd.h>
#include "malloc.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

static t_data			*first_extend(const size_t size)
{
	t_data			*ret = sbrk(0);
	size_t			page_size = getpagesize();
	size_t			final_size = page_size;

	final_size += (size + BLOCK_SIZE) / page_size * page_size;
	if (ret == (void *) -1 || sbrk(final_size) == (void *) -1)
		return (NULL);
	ret->size = size;
	ret->next = NULL;
	ret->prev = NULL;
	ret->available = 0;
	ret->ptr = ret->end;
	get_and_set_list(1, ret);
	get_and_set_size_break(final_size, 0);
	return (ret);
}

void				*malloc(size_t size)
{
	t_data			*ret = NULL;

	pthread_mutex_lock(&mutex);
	size = align_size(size);
	if (get_and_set_list(0, NULL) == NULL)
		ret = first_extend(size);
	else
		ret = extend_or_not(size);
	pthread_mutex_unlock(&mutex);
	if (ret == NULL)
		return (NULL);
	return (ret->end);
}
