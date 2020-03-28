/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:10:31 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/12 21:27:46 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_blk	*find_free_block(t_heap_type type, size_t size)
{
	t_heap	*heap;
	t_blk	*blk;

	if (g_heap == NULL)
	{
		blk = create_heap(NULL, size);
		g_heap = (void*)blk - BLK_SIZE;
		return (blk);
	}
	heap = g_heap;
	while (heap)
	{
		if (heap->type == type)
		{
			if ((blk = scrolling_blocks(heap->start, size)) == NULL \
					&& heap->next == NULL)
				return (create_heap(heap, size));
			if (blk != NULL)
				return (blk);
		}
		if (heap->next == NULL)
			return (create_heap(heap, size));
		heap = heap->next;
	}
	return (NULL);
}

t_bool			is_our_blok(void *addr)
{
	t_heap	*heap;
	void	*first_addr;
	void	*last_addr;

	heap = g_heap;
	if (addr == NULL)
		return (FALSE);
	while (heap)
	{
		first_addr = (void*)heap;
		last_addr = (void*)heap + heap->size;
		if (addr > first_addr && addr < last_addr)
			return (check_blk(heap, GET_BLOCK(addr)));
		heap = heap->next;
	}
	return (FALSE);
}

void			*malloc(size_t size)
{
	t_blk				*blk;
	const t_heap_type	type_heap = get_heap_type(size);

	if (size == 0)
		return (NULL);
	blk = find_free_block(type_heap, size);
	return (allocation_block(blk, size));
}

int 			main()
{
	char *ch = (char*)malloc(1);
	free(ch);
	char *str = malloc(100);
	free(str);

	str = malloc(15);
	// print_alloc_mem(g_heap)
	return (0);
}
