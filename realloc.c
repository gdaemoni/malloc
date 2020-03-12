/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:10:28 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/12 20:35:03 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*re_allocation_here(t_blk *blk, t_blk *next, size_t size)
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

static void		*re_allocation_move(t_blk *blk, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	free(blk->data);
	return (ft_memcpy(ptr, blk->data, blk->size));
}

void			*realloc(void *addr, size_t size)
{
	t_blk	*blk;
	t_blk	*next_blk;

	if (size == 0)
	{
		free(addr);
		return (NULL);
	}
	blk = GET_BLOCK(addr);
	if (!(is_our_blok(blk)))
		return (malloc(size));
	if (blk->size >= size)
		return (addr);
	next_blk = blk->next;
	if (next_blk->is_free && (next_blk->size) >= (size - blk->size))
		return (re_allocation_here(blk, next_blk, size));
	else
		return (re_allocation_move(blk, size));
}
