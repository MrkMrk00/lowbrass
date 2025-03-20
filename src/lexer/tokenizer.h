#ifndef LB_TOKENIZER_H
#define LB_TOKENIZER_H

#include "support/arena.h"

typedef enum
{
    T_PLUS,
    T_MINUS,

    T_NUMBER,
    T_STRING,
    T_IDENT,
} lb_tokentype_e;

typedef struct
{
    lb_tokentype_e type;
    const char* literal;
    uint32_t line;
} lb_token_t;

typedef struct
{
    lb_token_t* data;
    uint32_t size, capacity;
} lb_tokenlist_t;

lb_tokenlist_t lb_tokenizer_parse_module(lb_arena_t* arena,
                                         const char* filename);

#endif
