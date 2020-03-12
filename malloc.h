/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:10:36 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/12 21:11:50 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include "ft_mem.h"

# define PAGE_SIZE	((size_t)getpagesize())
# define TINY_SIZE	(PAGE_SIZE * 8)
# define SMALL_SIZE	(PAGE_SIZE * 32)
# define BLK_SIZE	(sizeof(t_blk))
# define HEAP_SIZE	(sizeof(t_heap))
# define GET_BLOCK(addr) ((t_blk*)(addr - BLK_SIZE))
# define LARGE_SIZE(size) ((size + HEAP_SIZE + (BLK_SIZE * 2)))
# define TYNY_MAX_ALLOC (256)
# define SMALL_MAX_ALLOC (1024)

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum		e_heap_type
{
	NUL,
	TYNY,
	SMALL,
	LARGE
}					t_heap_type;

typedef struct		s_blk
{
	struct s_blk	*next;
	struct s_blk	*pre;
	void			*data;
	size_t			size;
	t_bool			is_free;
}					t_blk;

typedef struct		s_heap
{
	struct s_heap	*next;
	struct s_heap	*pre;
	t_blk			*start;
	size_t			size;
	t_heap_type		type;
}					t_heap;

void				*malloc(size_t size);
void				*realloc(void *addr, size_t size);
void				*calloc(size_t number, size_t size);
void				free(void *addr);

void				hex_dump(const void *addr, const size_t size);
void				print_alloc_mem(const t_heap *heap);

t_bool				is_our_blok(void *addr);
t_heap_type			get_heap_type(size_t size);
size_t				get_heap_size(size_t size);
t_blk				*create_heap(t_heap *pre_hip, size_t size);
t_blk				*scrolling_blocks(t_blk *blk, size_t size);
t_bool				check_blk(t_heap *heap, t_blk *blk);
void				*allocation_block(t_blk *blk, size_t size);

#endif
