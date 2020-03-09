#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

typedef enum s_bool {FALSE, TRUE} t_bool;
typedef enum s_heap_type {NUL, TYNY, SMALL, LARGE} t_heap_type;

void	hex_dump(const void *addr, const size_t size);


typedef struct 		s_blk
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
	t_heap_type		type;
}					t_heap;

static t_heap		*g_heap;

#define TINY_SIZE	((size_t)getpagesize())
#define SMALL_SIZE	((size_t)getpagesize() * 8)
#define BLK_SIZE	(sizeof(t_blk))
#define HEAP_SIZE	(sizeof(t_heap))
#define TYNY_MAX_ALLOC (128)
#define SMALL_MAX_ALLOC (1024)

size_t		get_heap_size(size_t size)
{
	if (size < TYNY_MAX_ALLOC)
		return (TINY_SIZE);
	if (size < SMALL_MAX_ALLOC)
		return (SMALL_SIZE);
	return (TINY_SIZE * ((TINY_SIZE / size) + 1));
}

t_heap_type	get_heap_type(size_t size)
{
	if (size < TYNY_MAX_ALLOC)
		return (TYNY);
	if (size < SMALL_MAX_ALLOC)
		return (SMALL);
	return (LARGE);
}

t_heap		*init_heap(t_heap *pre_heap, void *addr, size_t size_heap, size_t size)
{
	t_heap	*new_heap;

	new_heap = (t_heap*)addr;
	new_heap->start = (t_blk*)(addr + HEAP_SIZE);
	new_heap->type = get_heap_type(size);
	new_heap->next = NULL;
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

t_heap		*create_heap(t_heap *pre_hip, size_t size)
{
	void			*addr;
	const size_t	heap_size = get_heap_size(size);

	addr = mmap(
		0, heap_size,
		PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE,
		-1, 0);
	if (addr == MAP_FAILED)
		return (NULL);
	return (init_heap(pre_hip, addr, heap_size, size));
}

t_blk		*scrolling_blocks(t_blk *blk, size_t size)
{
	while (!(blk->is_free) || blk->size < size)
	{
		blk = blk->next;
		if (!blk)
			return (NULL);
	}
	return (blk);
}

t_blk		*find_free_block(t_heap_type type, size_t size)
{
	t_heap	*heap;
	t_blk	*blk;

	if (g_heap == NULL)
	{
		g_heap = create_heap(NULL, size);
		return (g_heap->start);
	}
	heap = g_heap;
	while (heap)
	{
		if (heap->type == type)
		{
			if ((blk = scrolling_blocks(heap->start, size)) == NULL)
			{
				heap = create_heap(heap, size);
				return (heap->start);
			}
			return (blk);
		}
		if (heap->next == NULL)
		{
			heap = create_heap(heap, size);
			return (heap->start);
		}
		heap = heap->next;
	}
	return (NULL);
}

void		*allocation_block(t_blk *blk, size_t size)
{
	t_blk	*new_blk;

	new_blk = blk->data + size;
	new_blk->data = blk->data + size + BLK_SIZE;
	new_blk->is_free = TRUE;
	new_blk->size = blk->size - size;
	new_blk->pre = blk;
	new_blk->next = NULL;
	blk->size = size;
	blk->next = new_blk;
	blk->is_free = FALSE;
	return (blk->data);
}

void		*malloc(size_t size)
{
	t_blk				*blk;
	t_heap				*heap;
	const t_heap_type	type_heap = get_heap_type(size);

	blk = find_free_block(type_heap, size);
	return (allocation_block(blk, size));
}

void		free(void *addr)
{
	t_blk	*blk;
	t_blk	*blk_pre;

	blk = addr - BLK_SIZE;
	blk->is_free = TRUE;
	blk_pre = blk->pre;
	if (blk_pre != NULL && blk_pre->is_free)
	{
		
	}
}

int main()
{
	char *str0;
	char *str1;
	char *str2;
	char *str3;

	str0 = (char*)malloc(32);
	str1 = (char*)malloc(32);
	str2 = (char*)malloc(32);
	str3 = (char*)malloc(32);
	free(str0);
	free(str1);
	memset(str0, 'A', 31);
	memset(str1, 'B', 31);
	memset(str2, 'C', 31);
	memset(str3, 'D', 31);
	hex_dump(g_heap, 400);
	printf("\n");
	hex_dump(g_heap->next, 400);

	return (0);
}