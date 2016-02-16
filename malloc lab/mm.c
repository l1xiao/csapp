/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Li Xiao",
    /* First member's email address */
    "lixiao@link.cuhk.edu.hk",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};
/* Basic constants and macros */
#define WSIZE       4
#define DSIZE       8
#define CHUNKSIZE   (1<<12)
#define ALIGNMENT   8 /* single word (4) or double word (8) alignment */

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size)  (((size) + (ALIGNMENT-1)) & ~0x7)

#define MAX(x, y)   ((x) < (y)? (x) : (y))

#define PACK(size, alloc)   ((size) | (alloc))
/* read and write a word in address p */
#define GET(p)          (*(unsigned int *)(p))
#define PUT(p, val)     (*(unsigned int *)(p) = (val))
/* read the size and allocated fields from address p */
#define GET_SIZE(p)     (GET(p) & ~0x7)
#define GET_ALLOC(p)    (GET(P) & 0x1)
/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)        ((char *)(bp) - WSIZE)
#define FTRP(bp)        ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* global variable */
static void *heap_listp;

/* private functions */
static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);


/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 0);                             /* Alignment padding */
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));  /* Prologue header */
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));  /* prologue footer */
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1);
    heap_listp += (2 * WSIZE);

    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
        return -1;
    return 0;
}

static void *extend_heap(size_t words) {
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1) {
        return NULL;
    }
    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp), PACK(0, 1));

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    /* Ignore spurious requests */
    if (size == 0) {
        retun NULL;
    }

    /* Adjust block size to include overhead and alignment reqs */
    if (size <= DSIZE) {
        asize = 2 * DSIZE;
    } else {
        asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
    }

    /* search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL) {
        return NULL;
    }
    place(bp, asize);
    return bp;
}

/*
 * find a fit free block
 * return the start address of payload if success
 * return NULL if fail
 */
static void *find_fit(size_t asize) {
    void *bp;
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if ( !GET_ALLOC(HDRP(bp)) && asize <= GET_SIZE(HDRP(bp))) {
            return bp;
        }
    }
    return NULL;
}

/*
 * Place reqs at start address of free block
 * Split the rest block iff the size of rest is greater or equal to the least size
 */
static void place(void *bp, size_t asize) {
    size_t free_size = GET_SIZE(HDRP(bp));

    /* split */
    if (free_size - asize >= 2 * DSIZE) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(free_size - asize, 0));
        PUT(FTRP(bp), PACK(free_size - asize, 0));
    }
    /* not split */
    else {
        PUT(HDRP(bp), PACK(free_size, 1));
        PUT(FTRP(bp), PACK(free_size, 1));
    }
}

/*
 * clear allocated field in header and footer. Coalesce if possible.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

/*
 * Coalesce the possible free block. return the new start address
 */
static void *coalesce(void *bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    /* Case 1 */
    if (!prev_alloc && !next_alloc) {
        return bp;
    }
    /* Case 2 */
    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE((FTRP(bp) + WSIZE));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        return bp;
    }
    /* Case 3 */
    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE((HDRP(bp) - WSIZE));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        bp = PREV_BLKP(bp);
        return bp;
    }
    /* Case 4 */
    else {
        size += GET_SIZE((HDRP(bp) - WSIZE)) + GET_SIZE((FTRP(bp) + WSIZE));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
        return bp;
    }
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














