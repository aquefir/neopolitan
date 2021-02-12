/****************************************************************************\
 *                             neopolitan himem                             *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "gbabios.h"

#include <uni/types/int.h>

enum
{
	EWRAM    = 0x200000,
	EWRAM_SZ = 0x40000
};

/* HIMEM Heap Management System
 *
 * This is a system implemented to provide dynamic memory management
 * (malloc, the heap) for the GBA. It uses a double-ended queue mechanism
 * to store metadata for allocations, and works with EWRAM. The first
 * allocation is always at the beginning of EWRAM.
 *
 * Allocation metadata has been packed to minimise space. The first field,
 * wordsz, is the size of the allocation in words, i.e. multiples of 4 bytes.
 * The second field is nominally a pointer to the next allocation, but it too
 * has also been packed; it assumes that the memory region is EWRAM always,
 * and takes advantage of the fact that the size of EWRAM is 0x40000 bytes
 * along with the enforcement of word alignment to store the pointer as a
 * word count (LSR it by 2 and OR it with 0x2000000 to get the address).
 */

enum
{
	MAGICNUM         = 0x496F,
	FLAGS_INUSE_MASK = 0x8000,
	FLAGS_MAGIC_MASK = 0x7FFF
};

struct alloc
{
	u16 flags;
	u16 wordsz;
	u16 next;
	u16 prev;
} PACKED;

void initheap( void )
{
	struct alloc * head = (struct alloc *)EWRAM;

	/* no initialisation yet. make one big block now */
	head->flags  = MAGICNUM;
	head->wordsz = ( EWRAM_SZ >> 2 ) - 1;
	head->next   = ( (ptri)head >> 2 ) & 0xFFFF;
	head->prev   = head->next;
}

ptri _memsize( void * p )
{
	struct alloc * head = (struct alloc *)EWRAM;
	struct alloc * cur;

	for( cur = (struct alloc *)( ( (ptri)head->next << 2 ) | EWRAM );
		(struct alloc *)( ( cur->next << 2 ) | EWRAM ) != head;
		cur = (struct alloc *)( ( (ptri)cur->next << 2 ) | EWRAM ) )
	{
		if( (u8 *)cur + sizeof( struct alloc ) == p )
		{
			return cur->wordsz << 2;
		}
	}

	return 0;
}

void * malloc( ptri sz )
{
	/* Align to 4 bytes */
	if( sz & 3 )
	{
		sz &= ~3;
		sz++;
	}

	if( sz == 0 || sz > 0x40000 )
	{
		_bios_halt( );
	}

	{
		struct alloc * head = (struct alloc *)EWRAM;
		struct alloc * pos  = (struct alloc *)EWRAM;
		u32 foundsz;

		for( ;; )
		{
			if( !( pos->flags & FLAGS_INUSE_MASK ) )
			{
				foundsz = pos->wordsz << 2;

				if( foundsz < sz )
				{
					continue;
				}

				/* block is big enough to use, but how big? */
				if( foundsz - sz <
					( sizeof( struct alloc ) << 1 ) )
				{
					/* it isn’t much bigger than requested
					 * size just use it */
					pos->flags |= FLAGS_INUSE_MASK;
				}
				else
				{
					/* block is much bigger than requested
					 * size split off the rest */
					struct alloc * split;
					struct alloc * temp;

					foundsz -= sizeof( struct alloc ) + sz;

					split = (struct alloc *)( pos +
						sizeof( struct alloc ) + sz );
					pos->flags |= FLAGS_INUSE_MASK;
					pos->wordsz = sz >> 2;

					split->flags  = MAGICNUM;
					split->wordsz = foundsz >> 2;
					split->prev =
						( (ptri)pos >> 2 ) & 0xFFFF;
					split->next =
						( (ptri)pos->next >> 2 ) &
						0xFFFF;

					pos->next =
						( (ptri)split >> 2 ) & 0xFFFF;

					temp = (struct
						alloc *)( ( split->next
								  << 2 ) |
						EWRAM );

					if( temp != head )
					{
						temp->prev =
							( (ptri)split >> 2 ) &
							0xFFFF;
					}

					return (u8 *)pos +
						sizeof( struct alloc );
				}
			}

			if( (struct alloc *)( ( pos->next << 2 ) | EWRAM ) ==
				head )
			{
				return NULL;
			}

			pos = (struct alloc *)( ( pos->next << 2 ) | EWRAM );
		}
	}
}

void free( void * ptr )
{
	if( !ptr )
	{
		_bios_halt( );
	}

	{
		struct alloc * head = (struct alloc *)EWRAM;
		struct alloc * blk =
			(struct alloc *)( (u8 *)ptr - sizeof( struct alloc ) );
		struct alloc * next =
			(struct alloc *)( ( blk->next << 2 ) | EWRAM );

		blk->flags &= ~FLAGS_INUSE_MASK;

		/* if the freed block is not last, merge it with the next block
		 * if it is also not in use */

		if( next != head && !( next->flags & FLAGS_INUSE_MASK ) )
		{
			blk->wordsz +=
				( sizeof( struct alloc ) >> 2 ) + next->wordsz;
			next->flags &= ~FLAGS_MAGIC_MASK;
			blk->next = ( next->next >> 2 ) & 0xFFFF;
			next = (struct alloc *)( ( blk->next << 2 ) | EWRAM );

			if( next != head )
			{
				next->prev = ( (ptri)blk >> 2 ) & 0xFFFF;
			}
		}

		/* if the freed block is not first, merge it with the previous
		 * block if it is also not in use */
		if( blk != head )
		{
			struct alloc * prev =
				(struct alloc *)( ( blk->prev << 2 ) | EWRAM );
			struct alloc * next =
				(struct alloc *)( ( blk->next << 2 ) | EWRAM );

			if( !( prev->flags & FLAGS_INUSE_MASK ) )
			{
				prev->next = blk->next;

				if( next != head )
				{
					next->prev = blk->prev;
				}

				blk->flags &= ~FLAGS_MAGIC_MASK;
				prev->wordsz +=
					( sizeof( struct alloc ) >> 2 ) +
					blk->wordsz;
			}
		}
	}
}
