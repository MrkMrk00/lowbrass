#ifndef LB_BUFFER_H
#define LB_BUFFER_H

#include <stddef.h>

typedef struct
{
    size_t size;
    char* data;
} lb_buffer_t;

void buffer_free(lb_buffer_t* buf);

#endif
