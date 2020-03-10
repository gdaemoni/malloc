/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:53:06 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/07 19:16:20 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

void	hex_dump(const void *addr, size_t size)
{
	int				i;
	unsigned char	buff[17];
	unsigned char*	ptr;
	
	i = -1;
	ptr = (unsigned char*)addr;
	while (++i < size)
	{
		if ((i % 16) == 0)
		{
			if (i != 0)
				printf("  %s\n", buff);
			printf("%p ", &(ptr[i]));
		}
		if ((i % 2) && i > 0)
			printf("  %02x%02x", ptr[i - 1], ptr[i]);
		if (ptr[i] < 32 || ptr[i] > 126)
			buff[i % 16] = '.';
		else
			buff[i % 16] = ptr[i];
		buff[(i % 16) + 1] = 0;
	}
	printf("\n");
}

void	print_bloks(const t_blk *blk)
{
	char	*str0 = "|||||||||||||||";
	char	*str1 = "...............";

	while (blk)
	{
		printf("%p %s S%zu]  ", blk, (blk->is_free ? str1 : str0), blk->size);
		blk = blk->next;
	}
	printf("\n");
}

void	print_alloc_mem(const t_heap *heap)
{
	char	*str0 = "|||||||||||||||";
	char	*str1 = "...............";
	t_blk	*blk;
	int		i;

	i = 0;
	while (heap)
	{
		printf("HEAP N%d  addr %p\n", i++, heap);
		blk = heap->start;
		while (blk)
		{
			printf("%p %s S%zu]  ", blk, (blk->is_free ? str1 : str0), blk->size);
			blk = blk->next;
		}
		heap = heap->next;
		printf("\n");
	}
	printf("\n");
}
