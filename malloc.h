#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

# define TINY_SIZE	((size_t)getpagesize())
# define SMALL_SIZE	((size_t)getpagesize() * 8)
# define BLK_SIZE	(sizeof(t_blk))
# define HEAP_SIZE	(sizeof(t_heap))
# define GET_BLOCK(addr) ((t_blk*)(addr - BLK_SIZE))
# define TYNY_MAX_ALLOC (128)
# define SMALL_MAX_ALLOC (1024)

typedef enum		s_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum		s_heap_type
{
	NUL,
	TYNY,
	SMALL,
	LARGE
}					t_heap_type;

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
	size_t			size;
	t_heap_type		type;
}					t_heap;

static t_heap		*g_heap;

void				free(void* addr);

void				hex_dump(const void *addr, const size_t size);
void				print_alloc_mem(const t_heap *heap);

