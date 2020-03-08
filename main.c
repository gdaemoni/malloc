/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:42:55 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/08 14:22:57 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>

void	hex_dump(void* ptr, size_t size);

typedef enum s_bool {FALSE, TRUE} t_bool;

typedef struct 		s_blk
{
	struct s_blk	*next;
	void			*data;
	size_t			size;
	t_bool			is_free;
}					t_blk;

typedef struct		s_heap
{
	t_blk			*start;
	size_t			size_free;
	size_t			size;
}					t_heap;

static t_heap	*heap;

#define TINY_SIZE	((size_t)getpagesize())
#define BLK_SIZE	(sizeof(t_blk))
#define HEAP_SIZE	(sizeof(t_heap))

size_t	get_heap_size(size_t size)
{
	if (size < TINY_SIZE)
		return (TINY_SIZE);
	size = (TINY_SIZE / size) + 1;
	return (TINY_SIZE * size);
}

t_heap	*init_heap(const size_t size)
{
	void			*begin_addr;
	const size_t	size_alloc = get_heap_size(size + HEAP_SIZE); 
	
	begin_addr = mmap(
		0, size_alloc,
		PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE,
		-1, 0);
	if (begin_addr == MAP_FAILED)
		return (NULL);
	heap = (t_heap*)begin_addr;
	heap->start = (t_blk*)(begin_addr + HEAP_SIZE);
	heap->size_free = size_alloc - HEAP_SIZE;
	heap->size = size_alloc;
	heap->start->next = NULL;
	heap->start->data = begin_addr + HEAP_SIZE + BLK_SIZE;
	heap->start->is_free = TRUE;
	heap->start->size = heap->size_free - BLK_SIZE;
	return (heap);
}

void	*create_new_blk(t_blk *blk, size_t size)
{
	t_blk *new_blk;
	
	new_blk = blk->data + size;
	new_blk->data = blk->data + size;
	new_blk->size = blk->size - size;
	new_blk->next = NULL;
	new_blk->is_free = TRUE;
	blk->is_free = FALSE;
	blk->size = size;
	blk->next = new_blk;
	// printf("data %p === free = %d === next %p === size = %zu\n", new_blk->data, new_blk->is_free, new_blk->next, new_blk->size);
	return (blk->data);
}

void	*alloc_mem(size_t size)
{
	t_blk	*blk;
	blk = heap->start;
	
	// printf("heap %p\n", heap);
	// printf("size = %zu === size_f = %zu === start_p %p\n", heap->size, heap->size_free, heap->start);
	// printf("data %p === free = %d === next %p === size = %zu\n", blk->data, blk->is_free, blk->next, blk->size);
	while ((!(blk->is_free) || blk->size < size) && blk->next)
		blk = blk->next;
	
	if (!(blk->is_free))
	{
		printf("NOT FREE MEMORY\n");
		exit(1);
	}
	return (create_new_blk(blk, size));
}

void	*ft_malloc(size_t size)
{
	if (heap == NULL)
		heap = init_heap(size);
	return (alloc_mem(size));
}

void	print_heap()
{
	t_blk *blk;
	
	int i = 0;
	printf("HEAP ptr %p\n", heap);
	blk = heap->start;
	printf("blk N[%d] ptr %p == size %zu\n", ++i, blk, blk->size);
	while (blk->next != NULL)
	{
		printf("blk N[%d] ptr %p == size %zu\n", ++i, blk, blk->size);
		blk = blk->next;
	}
}

int main()
{
	char *str;
	char *str1;
	char *str2;
	char *str3;

	// str = (char*)ft_malloc(32);
	// str1 = (char*)ft_malloc(32);
	// str2 = (char*)ft_malloc(32);
	// str3 = (char*)ft_malloc(32);
	// memset(str, 'W', 31);
	// memset(str1, 'S', 31);
	// memset(str2, 'T', 31);
	// memset(str3, '4', 31);
	// print_heap();
	char ch = 'a';
	for (int i = 0; i < 10; ++i)
	{
		str = (char*)ft_malloc(32);
		memset(str, ch++, 31);
		str[32] = '\0';
	}

	// strcpy(str1, "2qwertytuerhW1WWWWWWWWWWWWWWW");
	hex_dump(heap, 400);
	// printf("ptr %p == %s\n",str, str);
	// printf("ptr %p == %s\n",str1, str1);
	// printf("ptr %p == %s\n",str2, str2);
	// printf("ptr %p == %s\n",str3, str3);
	// // for (int i = 0; i < 10; ++i)
	// {
	// 	str = (char*)malloc(100);
	// }
	return (0);
}