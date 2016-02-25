#include <windows.h>
#include "my_crt.h"

#define HEAP_SIZE       (1024 * 1024 * 32)
#define HEADER_SIZE     sizeof(t_heap_header)

typedef struct heap_header {
    enum {
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD,
    } type;
    unsigned int size;
    struct heap_header* next;
    struct heap_header* prev;
}t_heap_header;

t_heap_header* g_header = NULL;

unsigned int getFreeHeapSize()
{
    t_heap_header* p;
    unsigned int ret = 0;

    p = g_header;

    while(p) {
        if (p->type == HEAP_BLOCK_FREE)
            ret += p->size;
        p = p->next;
    }

    return ret;
}

void free(void * _Memory)
{
    t_heap_header* header;
    t_heap_header* pre;
    t_heap_header* next;

    if (_Memory == NULL)
        return;

    header = (t_heap_header*)((char*)_Memory - HEADER_SIZE);
    header->type = HEAP_BLOCK_FREE;

    pre = next = header;
    while (pre->prev != NULL && pre->prev->type == HEAP_BLOCK_FREE) {
        pre->prev->size = pre->prev->size + pre->size;
        pre->prev->next = pre->next;
        if (pre->next != NULL)
            pre->next->prev = pre->prev;
        pre = pre->prev;
    }

    next = pre;
    while (next->next != NULL && next->next->type == HEAP_BLOCK_FREE) {
        next->size = next->size + next->next->size;
        next->next = next->next->next;
        if (next->next != NULL)
            next->next->prev = next;
        //next = next->next;
    }

    return;
}

void * malloc(unsigned int _Size)
{
    t_heap_header* header;

    if (_Size == 0)
        return NULL;
    
    header = g_header;

    while (header) {
        if (header->type == HEAP_BLOCK_FREE) {
            if (header->size >= _Size + HEADER_SIZE && header->size <= _Size + HEADER_SIZE * 2) {
                header->type = HEAP_BLOCK_USED;
                return ((char*)header + HEADER_SIZE);
            }
            else if (header->size > _Size + HEADER_SIZE * 2) {
                t_heap_header* next;
                next = (t_heap_header*)((char*)header + HEADER_SIZE + _Size);
                next->type = HEAP_BLOCK_FREE;
                next->size = header->size - HEADER_SIZE - _Size;
                next->next = header->next;
                next->prev = header;

                header->type = HEAP_BLOCK_USED;
                header->size = HEADER_SIZE + _Size; 
                header->next = next;
                return ((char*)header + HEADER_SIZE);
            }
        }
        header = header->next;
    }

    return NULL;
}

int heap_init()
{
    void* base = NULL;
    t_heap_header *header = NULL;

    base = VirtualAlloc(0, HEAP_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (base == NULL)
        return 0;

    header = (t_heap_header*)base;
    header->type = HEAP_BLOCK_FREE;
    header->size = HEAP_SIZE - HEADER_SIZE;
    header->next = NULL;
    header->prev = NULL;

    g_header = header;

    return 1;
}