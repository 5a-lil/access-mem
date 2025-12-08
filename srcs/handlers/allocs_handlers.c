
#include "includes.h"

void *alloc_handler(t_alloc **allocs, t_alloc **last_alloc, va_list options)
{
    size_t size = va_arg(options, size_t);
    alloc_pos alloc_origin = va_arg(options, t_pos);

    void *new_alloc = malloc(size); // create the malloc
    if (!new_alloc) { MALLOC_FAIL_DEBUG_LOG(); MALLOC_FAILED(); } // if failure we should FREE ALL and exit and close also all fds
    memset(new_alloc, 0, size);

    t_alloc *new_node = malloc(sizeof(t_alloc));
    if (!new_node) { free(new_alloc); MALLOC_FAIL_DEBUG_LOG(); MALLOC_FAILED(); } // if failure we should FREE ALL and exit and close also all fds
    new_node->_alloc = new_alloc;
    new_node->_alloc_pos = alloc_origin;
    new_node->_next = NULL;

    MALLOC_SUCCESS_DEBUG_LOG();
    if (!(*allocs)) return *allocs = new_node, *last_alloc = new_node, new_alloc; // if the list is empty add the malloc to the head;
    return (*last_alloc)->_next = new_node, *last_alloc = new_node, new_alloc;
}

void free_alloc_handler(t_alloc **allocs, t_alloc **last_alloc, va_list options)
{
    void *alloc_to_free = va_arg(options, void *);

    // if alloc list is empty
    if (!(*allocs)) { FREE_FAIL_DEBUG_LOG(); return; }
    
    // if the deleted node is head
    if ((*allocs)->_alloc == alloc_to_free) 
    {
        t_alloc *new_head = (*allocs)->_next;
        FREE_SUCCESS_DEBUG_LOG((*allocs));
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
            if (iterator == *last_alloc) *last_alloc = previous;
            FREE_SUCCESS_DEBUG_LOG(iterator);
            free(iterator->_alloc);
            free(iterator);
            return;
        }
        previous = iterator;
        iterator = iterator->_next;
    }

    // nothing was found
    FREE_FAIL_DEBUG_LOG();
}

void *register_alloc_handler(t_alloc **allocs, t_alloc **last_alloc, va_list options)
{
    void *new_alloc = va_arg(options, void *);
    alloc_pos alloc_origin = va_arg(options, t_pos);
    t_alloc *original_alloc = NULL;

    // allocation is already registered we dont register again
    if ((original_alloc = alloc_exists(allocs, new_alloc))) { REGISTER_ALLOC_ALREADY_REGISTERED_LOG(); REGISTER_FAILED(); };

    t_alloc *new_node = malloc(sizeof(t_alloc));
    if (!new_node) { REGISTER_ALLOC_FAIL_DEBUG_LOG(); MALLOC_FAILED(); } // if failure we should FREE ALL and exit and close also all fds
    new_node->_alloc = new_alloc;
    new_node->_alloc_pos = alloc_origin;
    new_node->_next = NULL;

    REGISTER_ALLOC_SUCCESS_DEBUG_LOG();
    if (!(*allocs)) return *allocs = new_node, *last_alloc = new_node, new_alloc; // if the list is empty add the malloc to the head;
    return (*last_alloc)->_next = new_node, *last_alloc = new_node, new_alloc;
}