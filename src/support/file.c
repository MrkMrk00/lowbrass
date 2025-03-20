#include "support/file.h"
#include "support/assert.h"

#include <stdlib.h>
#include <sys/stat.h>

long long file_size(const char* filename)
{
    struct stat st;

    // platform independant pls
    stat(filename, &st);

    return st.st_size;
}

int read_file(lb_arena_t* arena, lb_buffer_t* dest, const char* filename)
{
    fsize_t size = file_size(filename);
    if (size < 0) {
        return size;
    }

    dest->data = arena_alloc(arena, size);
    dest->size = size;

    FILE* fp = fopen(filename, "r");
    LB_ASSERT(fp);

    fread(dest->data, size, 1, fp);

    fclose(fp);

    return 0;
}
