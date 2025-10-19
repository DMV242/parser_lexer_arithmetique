#ifndef LEXER_H
#define LEXER_H

enum TokenType
{
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_EOF
};

struct Token
{
    enum TokenType type;
    char value[32];
};

struct TokenArray
{
    struct Token *tokens;
    int size;
    int capacity;
};

struct Token next_token(const char *input, int *i);
struct TokenArray *init_token_array(void);
void add_token(struct TokenArray *arr, struct Token token);
void free_token_array(struct TokenArray *arr);




#endif // !LEXER_H
