#include "support/file.h"
#include "support/assert.h"

#include <stdlib.h>
#include <sys/stat.h>

long long file_size(const char* filename)
{
    struct stat st;
    stat(filename, &st);

    return st.st_size;
}

int read_file(lb_buffer_t* dest, const char* filename)
{
    fsize_t size = file_size(filename);
    if (size < 0) {
        return size;
    }

    // TODO: check for malloc success? (pass in allocator, ...)
    dest->data = malloc(size);
    dest->size = size;

    FILE* fp = fopen(filename, "r");
    LB_ASSERT(fp);

    fread(dest->data, size, 1, fp);

    return 0;
}
