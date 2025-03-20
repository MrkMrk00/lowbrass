#define ARENA_IMPLEMENTATION
#include "lexer/tokenizer.h"
#include "support/arena.h"
#include <stdio.h>

int main(void)
{
    lb_arena_t arena = { 0 };
    lb_tokenlist_t tokens = lb_tokenizer_parse_module(&arena, "mod.lb");

    for (size_t i = 0; i < tokens.size; i++) {
        lb_token_t token = tokens.data[i];

        switch (token.type) {
            case T_PLUS:
                puts("T_PLUS(+)");
                break;
            case T_MINUS:
                puts("T_MINUS(-)");
                break;
            case T_NUMBER:
                printf("T_NUMBER(%s)\n", token.literal);
                break;
            default:
                puts("unknown");
        }
    }

    return 0;
}
