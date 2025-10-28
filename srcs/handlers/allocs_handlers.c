
#include "access_mem.h"

void *alloc_handler(t_alloc **allocs, size_t size)
{
    static t_alloc *last_alloc = NULL;

    void *new_alloc = malloc(size); // create the malloc
    if (!new_alloc) { printf("[%s]: Malloc of size [%zu] failed\n", ERROR_LOG, size); access_mem_NUKE(); return MALLOC_FAILED; } // if failure we should FREE ALL and exit and close also all fds
    memset(new_alloc, 0, size);


    t_alloc *new_node = malloc(sizeof(t_alloc));
    if (!new_node) { printf("[%s]: Malloc of new alloc node failed\n", ERROR_LOG); free(new_alloc); last_alloc = NULL; access_mem_NUKE(); return MALLOC_FAILED; } // if failure we should FREE ALL and exit and close also all fds
    new_node->_alloc = new_alloc;
    new_node->_next = NULL;

    if (!(*allocs)) return *allocs = new_node, last_alloc = new_node, new_alloc; // if the list is empty add the malloc to the head;
    return last_alloc->_next = new_node, last_alloc = new_node, new_alloc;
}

void free_alloc_handler(t_alloc **allocs, void *alloc_to_free)
{
    // if alloc list is empty
    if (!(*allocs)) { printf("[%s]: Address [%p] isn't dynamically allocated\n", BOLD_YELLOW, alloc_to_free); return; }
    
    // if the deleted node is head
    if ((*allocs)->_alloc == alloc_to_free) 
    {
        t_alloc *new_head = (*allocs)->_next;
        free((*allocs)->_alloc);
        free(*allocs);
        *allocs = new_head;
        return;
    }

    // if the deleted node is in the middle
    allocs_iterator iterator = *allocs;
    t_alloc *previous = NULL;
    while (iterator != NULL)
    {
        if (iterator->_alloc == alloc_to_free)
        {
            previous->_next = iterator->_next;
            free(iterator->_alloc);
            free(iterator);
            return;
        }
        previous = iterator;
        iterator = iterator->_next;
    }

    // nothing was found
    printf("[%s]: Address [%p] isn't dynamically allocated\n", WARNING_LOG, alloc_to_free);
}

void free_all_handler(t_alloc **allocs) { while ((*allocs) != NULL) access_mem_FREE_ALLOC((*allocs)->_alloc); }