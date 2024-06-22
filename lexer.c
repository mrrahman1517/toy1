#include "lexer.h"

T_token create_end_token() {
    T_token token = (T_token)malloc(sizeof(struct S_token));
    token->kind = END;
    return token;
}

T_token create_semicolon_token() {
    T_token token = (T_token)malloc(sizeof(struct S_token));
    token->kind = SEMICOLON;
    return token;
}

T_token create_number_token(char c) {
    T_token token = (T_token)malloc(sizeof(struct S_token));
    token->kind = NUMBER;
    token->number = c - '0';
    return token;
}

T_token create_operator_token(char c) {
    T_token token = (T_token)malloc(sizeof(struct S_token));
    token->kind = OPERATOR;
    token->character = c;
    return token;
}

void lexer_error() {
    fprintf(stderr, "lexer error\n");
    exit(1);
}   

T_token lex() {
    int c;
    while ((c = fgetc(stdin)) != EOF) {
        if (isspace(c)) {
            continue;
        } else
        if (isdigit(c)) {
            return create_number_token(c);
        } else if (c == ';') {
            return create_semicolon_token();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            return create_operator_token(c);
        } else {
            lexer_error();
        }
    }
    return create_end_token();
}