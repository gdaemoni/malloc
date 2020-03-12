/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:06:54 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/12 20:35:46 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_heap	*init_heap(\
	t_heap *pre_heap, void *addr, size_t size_heap, size_t size)
{
	t_heap	*new_heap;

	new_heap = (t_heap*)addr;
	new_heap->start = (t_blk*)(addr + HEAP_SIZE);
	new_heap->type = get_heap_type(size);
	new_heap->next = NULL;
	new_heap->size = size_heap;
	if (pre_heap != NULL)
	{
		new_heap->pre = pre_heap;
		pre_heap->next = new_heap;
	}
	new_heap->start->data = addr + HEAP_SIZE + BLK_SIZE;
	new_heap->start->is_free = TRUE;
	new_heap->start->size = size_heap - HEAP_SIZE - BLK_SIZE;
	new_heap->start->next = NULL;
	new_heap->start->pre = NULL;
	return (new_heap);
}

t_blk	*create_heap(t_heap *pre_hip, size_t size)
{
	void			*addr;
	t_heap			*heap;
	const size_t	heap_size = get_heap_size(size);

	addr = mmap(
		0, heap_size,
		PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE,
		-1, 0);
	if (addr == MAP_FAILED)
		return (NULL);
	heap = init_heap(pre_hip, addr, heap_size, size);
	return (heap->start);
}

t_blk	*scrolling_blocks(t_blk *blk, size_t size)
{
	while (!(blk->is_free) || blk->size < size + BLK_SIZE)
	{
		blk = blk->next;
		if (!blk)
			return (NULL);
	}
	return (blk);
}

void	*allocation_block(t_blk *blk, size_t size)
{
	t_blk	*new_blk;

	if (blk == NULL)
		return (NULL);
	if (blk->next != NULL)
	{
		blk->is_free = FALSE;
		return (blk->data);
	}
	new_blk = blk->data + size;
	new_blk->data = blk->data + size + BLK_SIZE;
	new_blk->is_free = TRUE;
	new_blk->size = blk->size - size - BLK_SIZE;
	new_blk->pre = blk;
	new_blk->next = NULL;
	blk->size = size;
	blk->next = new_blk;
	blk->is_free = FALSE;
	return (blk->data);
}
