#ifndef LB_FILE_H
#define LB_FILE_H

#include <stdint.h>
#include <stdio.h>

#include "support/buffer.h"

typedef long long fsize_t;

fsize_t file_size(const char* filename);

int read_file(lb_buffer_t* dest, const char* filename);

#endif
