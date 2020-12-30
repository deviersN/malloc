/*
** EPITECH PROJECT, 2018
** Nom_du_Projet
** File description:
** 
*/

#include <unistd.h>
#include "malloc.h"

size_t			align_size(size_t x)
{
	if (x == 0)
		return (x);
	x -= 1;
	x -= x % 8;
	x += x % 8 * 8;
	x += 8;
	return (x);
}

size_t			get_and_set_size_break(const size_t size,
const int add_minus)
{
	static size_t	size_break = 0;
	size_t		ret = 0;

	if (add_minus == 0) {
		size_break += size;
	}
	else {
		size_break -= size;
	}
	ret = size_break;
	return (ret);
}

t_data			*get_and_set_list(const int get_set, t_data *data)
{
	static void	*list = NULL;
	void		*ret = list;

	if (get_set == 1)
		list = data;
	return (ret);
}

t_data			*get_valid_node(void *data)
{
	t_data		*node = data - BLOCK_SIZE;
	t_data		*list = get_and_set_list(0, NULL);

	if (list == NULL || data == NULL ||
	data < (void *)list || data > data + get_and_set_size_break(0, 0))
		return (NULL);
	if (node->ptr == data)
		return (node);
	return (NULL);
}