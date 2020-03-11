#include "malloc.h"

void		free_heap(t_blk *blk)
{
	t_heap *heap;

	if (blk->pre == NULL && blk->next == NULL)
	{
		heap = (t_heap*)blk - HEAP_SIZE;
		munmap(heap, heap->size);
	}
}

t_bool		check_blk(t_heap *heap, t_blk *blk)
{
	t_blk	*actual_blk;

	actual_blk = heap->start;
	while (actual_blk)
	{
		if (actual_blk == blk)
			return (TRUE);
		actual_blk = actual_blk->next;
	}
	return (FALSE);
}

t_bool		is_our_blok(void *addr)
{
	t_heap	*heap;
	void	*first_addr;
	void	*last_addr;
	
	heap = g_heap;
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

void		free(void *addr)
{
	t_blk	*blk;
	t_blk	*blk_pre;

	if (addr == NULL || !(is_our_blok(addr)))
		return ;
	blk = GET_BLOCK(addr);
	blk->is_free = TRUE;
	blk_pre = blk->pre;
	if (blk_pre != NULL && blk_pre->is_free)
	{
		blk_pre->size += blk->size + BLK_SIZE;
		blk_pre->next = blk->next;
		blk_pre->next->pre = blk_pre;
		blk = blk_pre;
	}
	if (blk->next != NULL && blk->next->is_free)
	{
		blk->size += blk->next->size + BLK_SIZE;
		blk->next = blk->next->next;
		if (blk->next != NULL)
			blk->next->pre = blk;
	}
	free_heap(blk);
}
