/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** free function
*/

#include <unistd.h>
#include "malloc.h"

static void		reduce_break(t_data *data)
{
	void		*begin = get_and_set_list(0, NULL);
	const size_t	page_size = getpagesize();
	size_t		final_size = 0;
	size_t		new_size_node;

	if (data->prev == NULL) {
		get_and_set_list(1, NULL);
		brk(begin);
	}
	else if (data->size > page_size) {
		new_size_node = data->size / page_size *page_size;
		data->size -= new_size_node;
		final_size = get_and_set_size_break(new_size_node, 1);
		brk(begin + final_size);
	}
}

static void		fusion_prev(t_data *data)
{
	data->prev->size += data->size + BLOCK_SIZE;
	data->prev->next = data->next;
	if (data->next != NULL) {
		data->next->prev = data->prev;
	}
}

void			free(void *ptr)
{
	t_data		*data = get_valid_node(ptr);

	pthread_mutex_lock(&mutex);
	if (data != NULL) {
		data->available = 1;
		if (data->prev != NULL && data->prev->available == 1) {
			fusion_prev(data);
			data = data->prev;
		}
		if (data->next != NULL && data->next->available == 1) {
			fusion_prev(data->next);
		}
		if (data->next == NULL) {
			reduce_break(data);
		}
	}
	pthread_mutex_unlock(&mutex);
}