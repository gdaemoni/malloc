/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:28:10 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/12 21:29:10 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	free_heap(t_blk *blk)
{
	t_heap *heap;
	t_heap *pre_heap;

	if (blk->pre == NULL && blk->next == NULL)
	{
		heap = (void*)blk - HEAP_SIZE;
		if (heap->pre)
		{
			pre_heap = heap->pre;
			pre_heap->next = heap->next;
			if (heap->next)
				heap->next->pre = pre_heap;
		}
		else
			g_heap = NULL;
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
