/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** realloc
*/

#include <string.h>
#include "malloc.h"

static void		copy_value(t_data *old, t_data *new)
{
	char		*old_copy = NULL;
	char		*new_copy = NULL;
	unsigned int	i = 0;

	if (old != NULL && new != NULL) {
		old_copy = old->ptr;
		new_copy = new->ptr;
	}
	while (i < old->size) {
		new_copy[i] = old_copy[i];
		++i;
	}
	while (i < new->size) {
		new_copy[i] = '\0';
		++i;
	}
}

void			*realloc(void *ptr, size_t size)
{
	t_data		*old_data = get_valid_node(ptr);
	t_data		*new_data = NULL;
	size_t		new_size = align_size(size);
	void		*ret = NULL;

	pthread_mutex_lock(&mutex);
	if (old_data != NULL && old_data->size >= size) {
		pthread_mutex_unlock(&mutex);
		return (ptr);
	}
	pthread_mutex_unlock(&mutex);
	ret = malloc(new_size);
	pthread_mutex_lock(&mutex);
	new_data = get_valid_node(ret);
	if (old_data != NULL && new_data != NULL) {
		copy_value(old_data, new_data);
	}
	pthread_mutex_unlock(&mutex);
	free(ptr);
	return (ret);
}

void			*calloc(size_t nmenb, size_t size)
{
	void		*new = malloc(size * nmenb);
	t_data		*ret = NULL;

	pthread_mutex_lock(&mutex);
	if (new == NULL) {
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	memset(new, 0, size * nmenb);
	ret = get_valid_node(new);
	if (ret == NULL) {
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&mutex);
	return (ret->end);
}