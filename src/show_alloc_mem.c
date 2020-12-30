/*
** EPITECH PROJECT, 2018
** Malloc
** File description:
** show_alloc_mem function
*/

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void		show_alloc_mem(void)
{
	t_data	*tmp = get_and_set_list(0, NULL);
	void	*no_alloc_break = NULL;

	if (tmp != NULL) {
		printf("break : %p\n",
		(void *)(tmp) + get_and_set_size_break(0, 0));
		while (tmp != NULL) {
			printf("%p - %p : %ld bytes\n", tmp->ptr,
			tmp->ptr + tmp->size, tmp->size);
			tmp = tmp->next;
		}
	}
	else {
		no_alloc_break = sbrk(0);
		if (no_alloc_break == (void *) -1)
			printf("break : %p\n", no_alloc_break);
	}
}