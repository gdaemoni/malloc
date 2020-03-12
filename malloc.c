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

static t_heap	*g_heap;

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

void	test2(t_heap *heap, size_t count, size_t size)
{
	size_t		i;
	char		*str;
	
	i = 0;
	while (i < count)
	{
		str = malloc(size);
		i++;
	}
	print_alloc_mem(heap);
	printf("TEST 2 count = %zu size = %zu\n", count, size);
}

int 			main()
{
	size_t n = 100;
	test2(g_heap, 100, n);
	test2(g_heap, 1000, n);
	test2(g_heap, 10000, n);
	test2(g_heap, 100000, n);
	return (0);
}
