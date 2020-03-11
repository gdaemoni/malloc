#include "malloc.h"

void		*re_allocation_here(t_blk *blk, t_blk *next, size_t size)
{
	t_blk			*new_blk;

	if (next->next == NULL)
	{
		new_blk = blk->data + size;
		new_blk->pre = blk;
		new_blk->next = NULL;
		new_blk->size = next->size - (size - blk->size);
		new_blk->data = blk->data + size + BLK_SIZE;
		new_blk->is_free = TRUE;
		blk->next = new_blk;
		blk->size = size;
	}
	else
	{
		blk->next = next->next;
		next->next->pre = blk;
		blk->size += next->size + BLK_SIZE;
	}
	return (blk->data);
}

void		*re_allocation_move(t_blk *blk, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	memmove(ptr, blk->data, blk->size);
	free(blk->data);
	return (ptr);
}
void		*realloc(void *addr, size_t size)
{
	t_blk	*blk;
	t_blk	*next_blk;

	blk = GET_BLOCK(addr);
	if (size == 0)
	{
		free(addr);
		return (NULL);
	}
	if (addr == NULL)
		return (malloc(size));
	if (blk->size >= size)
		return (addr);
	next_blk = blk->next;
	if (next_blk->is_free && (next_blk->size) >= (size - blk->size))
		return (re_allocation_here(blk, next_blk, size));
	else
		return (re_allocation_move(blk, size));
}
