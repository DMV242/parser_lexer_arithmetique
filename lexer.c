#include "lexer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ctype.h"

struct TokenArray *init_token_array(void)
{
    struct TokenArray *arr = malloc(sizeof(struct TokenArray));
    if (!arr)
        return NULL;
    arr->capacity = 8;
    arr->size = 0;
    arr->tokens = malloc(arr->capacity * sizeof(struct Token));
    if (!arr->tokens)
    {
        free(arr);
        return NULL;
    }
    return arr;
}

void add_token(struct TokenArray *arr, struct Token token)
{
    if (arr->size >= arr->capacity)
    {
        int new_capacity = arr->capacity * 2;
        struct Token *tmp =
            realloc(arr->tokens, new_capacity * sizeof(struct Token));
        if (!tmp)
        {
            printf("Erreur mémoire\n");
            exit(1);
        }
        arr->tokens = tmp;
        arr->capacity = new_capacity;
    }
    arr->tokens[arr->size++] = token;
}

void free_token_array(struct TokenArray *arr)
{
    free(arr->tokens);
    arr->tokens = NULL;
    arr->size = 0;
    arr->capacity = 0;
    free(arr);
    arr = NULL;
}

struct Token next_token(const char *input, int *i)
{
    bool is_digit_found = false;
    int token_len = 0;
    struct Token token = { .type = TOKEN_EOF, .value = { 0 } };
    for (int j = *i; input[j] != '\0'; j++)
    {
        if (isdigit(input[j]))
        {
            if (!is_digit_found)
            {
                token.type = TOKEN_NUMBER;
                token.value[token_len] = input[j];
                is_digit_found = true;
            }
            else
            {
                token.value[token_len] = input[j];
            }
            token_len++;
            (*i)++;
        }
        else if ((input[j] == '+' || input[j] == '-' || input[j] == '*'
                  || input[j] == '/' || input[j] == '%')
                 && (!is_digit_found))
        {
            token.type = TOKEN_OPERATOR;
            token.value[token_len] = input[j];
            token.value[token_len + 1] = '\0';
            (*i)++;
            return token;
        }
        else if ((input[j] == '(' || input[j] == ')') && (!is_digit_found))
        {
            token.type = input[j] == '(' ? TOKEN_LEFT_PAREN : TOKEN_RIGHT_PAREN;
            token.value[token_len] = input[j];
            token.value[token_len + 1] = '\0';
            (*i)++;
            return token;
        }
        else
        {
            if (!is_digit_found)
            {
                (*i)++;
                continue;
            }
            else
            {
                token.value[token_len] = '\0';
                return token;
            }
        }
    }
    return token;
}
