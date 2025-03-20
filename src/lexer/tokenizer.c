#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include "lexer/tokenizer.h"
#include "support/arena.h"
#include "support/assert.h"
#include "support/buffer.h"
#include "support/file.h"

#define TOKENLIST_INIT_CAPACITY 128
#define TOKENLIST_GROW_FACTOR 2

typedef struct
{
    lb_arena_t* arena;
    lb_buffer_t source;
    lb_tokenlist_t tokenlist;
    uint32_t position, line;
    uint32_t start;
} tokenizer_state_t;

void tokenizer_state_init(tokenizer_state_t* t, lb_arena_t* arena)
{
    t->arena = arena;

    t->source.data = NULL;
    t->source.size = 0;

    t->tokenlist.size = 0;
    t->tokenlist.capacity = TOKENLIST_INIT_CAPACITY;
    t->tokenlist.data =
      arena_alloc(t->arena, sizeof(lb_token_t) * t->tokenlist.capacity);

    t->position = 0;
    t->line = 1;
}

static void tokenlist_ensure_capacity(tokenizer_state_t* t, size_t new_size)
{
    uint32_t new_capacity = t->tokenlist.capacity;
    while (new_capacity < new_size) {
        new_capacity *= TOKENLIST_GROW_FACTOR;
    }

    if (new_capacity == t->tokenlist.capacity) {
        return;
    }

    size_t old_alloc_size =
      t->tokenlist.capacity * sizeof(t->tokenlist.data[0]);
    size_t new_alloc_size = new_capacity * sizeof(t->tokenlist.data[0]);

    t->tokenlist.data = arena_realloc(
      t->arena, t->tokenlist.data, old_alloc_size, new_alloc_size);
    LB_ASSERT(t->tokenlist.data);

    t->tokenlist.capacity = new_capacity;
}

static void push_token(tokenizer_state_t* s,
                       const char* literal,
                       lb_tokentype_e type)
{

    tokenlist_ensure_capacity(s, s->tokenlist.size + 1);

    s->tokenlist.data[s->tokenlist.size++] = (lb_token_t){
        .literal = literal,
        .type = type,
        .line = s->line,
    };
}

static inline char advance(tokenizer_state_t* t)
{
    if (t->source.size <= t->position) {
        return '\0';
    }

    return t->source.data[t->position++];
}

static inline char peek(const tokenizer_state_t* t)
{
    if (t->source.size <= t->position) {
        return '\0';
    }

    return t->source.data[t->position];
}

static inline void read_number(tokenizer_state_t* s)
{
    while (isdigit(peek(s))) {
        advance(s);
    }

    size_t lit_size = s->position - s->start;

    // Add one for the 0 terminator.
    char* literal = arena_alloc(s->arena, sizeof(char) * lit_size + 1);

    strncpy(literal, s->source.data + s->start, lit_size);
    literal[lit_size] = '\0';

    push_token(s, literal, T_NUMBER);
}

lb_tokenlist_t lb_tokenizer_parse_module(lb_arena_t* arena,
                                         const char* filename)
{
    tokenizer_state_t state;
    tokenizer_state_init(&state, arena);

    read_file(arena, &state.source, filename);

    char ch;
    while ((ch = advance(&state)) != '\0') {
        state.start = state.position - 1;

        if (ch == '\n') {
            state.line++;
        }

        if (isspace(ch)) {
            continue;
        }

        switch (ch) {
            case '+':
                push_token(&state, NULL, T_PLUS);
                break;

            case '-':
                push_token(&state, NULL, T_MINUS);
                break;
        }

        if (isdigit(ch)) {
            read_number(&state);
        }
    }

    return state.tokenlist;
}
