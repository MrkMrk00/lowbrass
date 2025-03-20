#include "support/buffer.h"
#include <stdlib.h>

void buffer_free(lb_buffer_t* buf)
{
    if (buf->data != NULL) {
        free(buf->data);
    }

    buf->size = 0;
}
