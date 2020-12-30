/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** Extension of malloc
*/

#include <unistd.h>
#include "malloc.h"

static t_data		*extend_data(t_data *data, const size_t size,
const size_t unused_memory, const size_t p_size)
{
	size_t		new_size = p_size;
	t_data		*new = (data->ptr + data->size);

	new_size += (size + BLOCK_SIZE - unused_memory) / p_size * p_size;
	if (sbrk(new_size) == (void *) -1)
		return (NULL);
	new->size = size;
	new->next = NULL;
	new->prev = data;
	new->prev->next = new;
	new->available = 0;
	new->ptr = new->end;
	get_and_set_size_break(new_size, 0);
	return (new);
}

static t_data		*split_data(t_data *data, const size_t size)
{
	t_data		*new = (data->ptr + data->size);

	new->size = size;
	new->next = NULL;
	new->prev = data;
	new->prev->next = new;
	new->available = 0;
	new->ptr = new->end;
	return (new);
}

static t_data		*create_new_data(const size_t size,
const size_t page_size)
{
	t_data		*tmp = get_and_set_list(0, NULL);
	size_t		unused_memory = 0;
	size_t		all_page = page_size;

	while (tmp->next != NULL) {
		unused_memory += tmp->size + BLOCK_SIZE;
		tmp = tmp->next;
	}
	unused_memory += tmp->size + BLOCK_SIZE;
	all_page += unused_memory / page_size * page_size;
	unused_memory = all_page - unused_memory;
	if (unused_memory > size + BLOCK_SIZE)
		return (split_data(tmp, size));
	return (extend_data(tmp, size, unused_memory, page_size));
}

static t_data		*cut_node(t_data *tmp, const size_t size,
const size_t page_size)
{
	t_data		*new;

	if (tmp->size > size + BLOCK_SIZE + 8) {
		new = tmp->ptr + size;
		new->size = tmp->size - size - BLOCK_SIZE;
		new->next = tmp->next;
		if (tmp->next != NULL)
			new->next->prev = new;
		new->prev = tmp;
		new->prev->next = new;
		new->available = 1;
		new->ptr = new->end;
		tmp->size = size;
		tmp->available = 0;
		return (tmp);
	}
	if (tmp->size == size)
		return (tmp);
	return (create_new_data(size, page_size));
}

t_data			*extend_or_not(const size_t size)
{
	t_data		*tmp = get_and_set_list(0, NULL);
	t_data		*prev_tmp = NULL;
	const size_t	page_size = getpagesize();
	size_t		unused_memory = 0;
	size_t		all_page = page_size;

	while (tmp != NULL &&
	!(tmp->available == 1 && tmp->size > size)) {
		unused_memory += tmp->size + BLOCK_SIZE;
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		return (cut_node(tmp, size, page_size));
	all_page += unused_memory / page_size * page_size;
	unused_memory = all_page - unused_memory;
	if (unused_memory > size + BLOCK_SIZE)
		return (split_data(prev_tmp, size));
	return (extend_data(prev_tmp, size, unused_memory, page_size));
}