
#include "../include/minishell.h"

void print_tokens(t_data *data)
{
    if (data == NULL || data->tokens == NULL) {
        printf("Data or tokens is NULL.\n");
        return;
    }

    char **tokens_0 = data->tokens[0];
    if (tokens_0 == NULL) {
        printf("Token at index 0 is NULL.\n");
        return;
    }

    printf("Token 0: %s\n", tokens_0[0]);

    char *token_0_0 = tokens_0[0];
    if (token_0_0 == NULL) {
        printf("Character at tokens[0][0] is NULL.\n");
        return;
    }

    printf("Character at tokens[0][0]: %c\n", *token_0_0);
    printf("Character at tokens[0][0][0]: %c\n", token_0_0[0]);
}
